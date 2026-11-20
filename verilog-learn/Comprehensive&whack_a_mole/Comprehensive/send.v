`timescale 1ns / 1ps

module send#(
    parameter DEBOUNCE_TIME = 24'd2000000 - 1 //消抖时间，默认为20ms，即0.02000000s
)
(
input wire clk,
input wire rst,
input wire btn,

output wire uart_tx,
output reg [7:0] cnt
);

//边沿检测 上升沿和下降沿均可
reg sig_r0;
reg sig_r1;

always @(posedge clk or posedge rst) begin
    if (rst)begin
        sig_r0 <= 1'b0;
        sig_r1 <= 1'b0;
    end
    else begin
        sig_r0 <= btn;
        sig_r1 <= sig_r0;
    end
end

wire btn_pos_edge = sig_r1 ^ sig_r0;

//实例化一个计数器, 拿来消抖
wire [24:0] CNT_debounced;
counter #(.CNT_MAX(DEBOUNCE_TIME)) u_counter_5  (
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b1),
    .reboot(btn_pos_edge),
    .auto_start(1'b0),
    .cnt(CNT_debounced)
    );

reg [6:0] count;

// 消抖发送按钮
reg btn_debounced;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        btn_debounced <= 1'd0;
    end
    else if (CNT_debounced == DEBOUNCE_TIME) begin
        btn_debounced <= btn;
    end
end

// 对消抖后的btn_debounced进行上升沿检测
reg sig_r2;
reg sig_r3;

always @(posedge clk or posedge rst) begin
    if (rst)begin
        sig_r2 <= 1'b0;
        sig_r3 <= 1'b0;
    end
    else begin
        sig_r2 <= btn_debounced;
        sig_r3 <= sig_r2;
    end
end

wire btn_debounced_pos_edge = ~sig_r3 & sig_r2;

// 消抖计数
always @(posedge clk or posedge rst) begin
    if (rst) begin
        count <= 2'd0;
    end

    else if (btn_debounced_pos_edge) begin
        if (count < 99) begin
            count <= count + 1;
        end
        else begin
            count <= 2'd0;
        end
    end
end

wire [3:0] count_ten = count / 7'd10;
wire [3:0] count_one = count % 7'd10;
always @(*) begin
    cnt = {count_ten, count_one};
end


// 发送的数据
reg [3:0] data_inx;
reg [7:0] send_data;
localparam DATA_INX_MAX = 4'd12;
always @(*) begin
    case (data_inx)
        4'd0 : send_data = "0";
        4'd1 : send_data = "7";
        4'd2 : send_data = "+";
        4'd3 : send_data = "2";
        4'd4 : send_data = "0";
        4'd5 : send_data = "2";
        4'd6 : send_data = "5";
        4'd7 : send_data = "3";
        4'd8 : send_data = "1";
        4'd9 : send_data = "0";
        4'd10 : send_data = "4";
        4'd11 : send_data = "1";
        4'd12 : send_data = "7";
        default: send_data = "!";
    endcase
end

// 实例化一个计数器，用于间隔0.00500000s发送不同字符
localparam CNT_LETTER_MAX = 19'd500000-1;
wire [24:0] cnt_letter;
counter #(.CNT_MAX(CNT_LETTER_MAX)) u_counter_4(
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b0),
    .reboot(btn_debounced_pos_edge),
    .auto_start(1'b0),
    .cnt(cnt_letter)
);

always @(posedge clk or posedge rst) begin
    if (rst) begin
        data_inx <= 4'b0; 
    end
    else if ((cnt_letter == CNT_LETTER_MAX) && (data_inx <= DATA_INX_MAX)) begin
        data_inx <= data_inx + 1;
    end
    else if (btn_debounced_pos_edge) begin
        data_inx <= 4'b0;
    end
    else if (data_inx > DATA_INX_MAX) begin
        data_inx <= data_inx;
    end
end

reg valid;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        valid <= 1'b0;
    end
    else if(btn_debounced_pos_edge || ((cnt_letter == CNT_LETTER_MAX) && (data_inx < DATA_INX_MAX))) begin
        valid <= 1'b1;
    end
    else begin
        valid <= 1'b0;
    end
end

// 实例化一个串口发送模块
uart_send u_uart_send (
    .clk(clk),
    .rst(rst),
    .valid(valid),
    .data(send_data),
    .dout(uart_tx)
);

endmodule
