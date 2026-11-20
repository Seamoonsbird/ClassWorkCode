`timescale 1ns / 1ps

module uart_recv(
    input                   clk,   
    input                   rst,   
    input                   din,   // 串口数据输入

    output reg              valid, // 为1表明输出的数据data有效，只维持一个时钟周期
    output reg [7:0]        data   
);

    localparam    IDLE  = 2'b00;
    localparam    START = 2'b01;
    localparam    DATA  = 2'b10;
    localparam    STOP  = 2'b11;

// 边沿检测din 下降沿
reg sig_r0;
reg sig_r1;

always @(posedge clk) begin
    if (rst) begin
        // 检测下降沿的时候复位需要将其置为1，否则当复位结束和第一个起始位产生同时进行的时候就会检测不到
        sig_r0 <= 1'b1;
        sig_r1 <= 1'b1;
    end
    else begin
        sig_r0 <= din;
        sig_r1 <= sig_r0;
    end
end
wire neg_edge = sig_r1 & ~sig_r0;

reg [1:0] current_state;
reg [1:0] next_state;

// 实例化一个计数器，用以发生采样信号
// 该计数器直接使用了实验四的计数器模块，因此会有一些多余的输入，比如pause，one，reboot等
localparam BAUD_CNT_MAX = 14'd10416-1;
wire [24:0] baud_cnt;
counter #(.CNT_MAX(BAUD_CNT_MAX)) U_counter_2 (
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b0),
    .reboot(neg_edge && current_state == IDLE),
    .auto_start(1'b0),
    .cnt(baud_cnt)
    );

// 产生采样信号
reg sam_sig;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        sam_sig <= 1'b0;
    end
    else if(baud_cnt == BAUD_CNT_MAX/2)begin
        sam_sig <= 1'b1;
    end
    else begin
        sam_sig <=1'b0;
    end
end

// 记录数据帧的第几位
reg [3:0] data_idx;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        data_idx <= 4'b0;
    end
    else if ((current_state == IDLE) || (data_idx > 4'd9)) begin
        data_idx <= 4'b0;
    end
    else if (data_idx <= 4'd10) begin
        if ((baud_cnt == BAUD_CNT_MAX) || neg_edge && current_state == IDLE) begin
            data_idx <= data_idx + 1;
        end
        else begin
            data_idx <= data_idx;
        end
    end
    else begin
        data_idx <= 4'b0;
    end
end

// 产生valid信号
always @(posedge clk or posedge rst) begin
    if (rst) begin
        valid <= 1'b0;
    end
    else if ((data_idx == 4'd9) && sam_sig) begin
        valid <= 1'b1;
    end
    else begin
        valid <= 1'b0;
    end
end

// 对数据进行采样
integer i;
reg [9:0] data_cache;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        for (i = 0; i<10; i = i+1) begin
            data_cache[i] <= 1'b1;
        end
    end
    else if (current_state == IDLE) begin
        for (i = 0; i<10; i = i+1) begin
            data_cache[i] <= 1'b1;
        end
    end
    else if (sam_sig) begin
        data_cache[data_idx] <= din;
    end
end

// 状态机三段式

// 第1个always块，描述次态迁移到现态
always @(posedge clk or posedge rst) begin
    if(rst)  current_state <= IDLE;
    else     current_state <= next_state;
end


// 第2个always块，描述状态转移条件判断
wire sig0 = baud_cnt == BAUD_CNT_MAX;
wire sig1 = data_cache[0] == 1'b0;
always @(*) begin
    case (current_state)
        IDLE : 
            if (neg_edge) begin
                next_state = START;
            end
            else begin
                next_state = IDLE;
            end
        START :
            if ((sig0) && (sig1)) begin
                next_state = DATA;
            end
            else begin
                next_state = START;
            end
        DATA :
            if ((baud_cnt == BAUD_CNT_MAX) && (data_idx == 4'd8)) begin
                next_state = STOP;
            end
            else begin
                next_state = DATA;
            end
        STOP :
            if ((baud_cnt == BAUD_CNT_MAX) && (data_idx == 4'd9)) begin
                next_state = IDLE;
            end
            else begin
                next_state = STOP;
            end
        default : next_state = IDLE; 
    endcase
end

// 第3个always块，描述输出逻辑，也可以用next_state作判断，对时序不敏感的电路两者都可以。
always @(posedge clk or posedge rst) begin
    if(rst) data <= 8'b0;
    else begin
        case(current_state)
            IDLE  :     data <= 8'b0;
            START :     data <= 8'd0;
            DATA  :     data <= 8'b0;
            STOP  :     data <= data_cache[8:1];
            default :   data <= 8'b0;
        endcase
    end
end

endmodule
