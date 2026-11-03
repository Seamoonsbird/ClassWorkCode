`timescale 1ns / 1ps

module led_ctrl_unit #(
    parameter CNT_MAX = 24'd200000-1   //与counter保持一致
)
(
    input wire rst,
    input wire clk,
    input wire [31:0] display,  // 待显示的8个十六进制字符
    output reg [7:0]  led_en,   // 位选信号
    output reg [7:0]  led_cx    // 段选信号，EGO1段选信号需16位或2组8位
);



//计数器，用于分频
wire [23:0] cnt;

counter #(.CNT_MAX(CNT_MAX)) u_counter_1  (
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b0),
    .reboot(1'b0),
    .cnt(cnt)
    );

//类似流水灯实现动态显示
reg [2:0] dis_inx;
always @(posedge clk or posedge rst) begin
    if (rst)begin
        dis_inx <= 3'o0;
    end
    else if (cnt == CNT_MAX) begin
        dis_inx <= dis_inx + 3'o1;
    end
end


//位选译码
reg [7:0] decode_inx;
always @(*) begin
    case (dis_inx)
        3'd0: decode_inx = 8'b1111_1110;
        3'd1: decode_inx = 8'b1111_1101;
        3'd2: decode_inx = 8'b1111_1011;
        3'd3: decode_inx = 8'b1111_0111;
        3'd4: decode_inx = 8'b1110_1111;
        3'd5: decode_inx = 8'b1101_1111;
        3'd6: decode_inx = 8'b1011_1111;
        3'd7: decode_inx = 8'b0111_1111;
        default: decode_inx = 8'b1111_1111;
    endcase
end

//位选信号
always @(posedge clk or posedge rst) begin
    if (rst)begin
        led_en <= 8'hff;
    end
    else begin
        led_en <= decode_inx;
    end
end


//取数据
reg [3:0] decode_data;
always @(*) begin
    case (dis_inx)
        3'd0 : decode_data = display[3:0];
        3'd1 : decode_data = display[7:4];
        3'd2 : decode_data = display[11:8];
        3'd3 : decode_data = display[15:12];
        3'd4 : decode_data = display[19:16];
        3'd5 : decode_data = display[23:20];
        3'd6 : decode_data = display[27:24];
        3'd7 : decode_data = display[31:28];
        default: decode_data = 4'd0;
    endcase
end

//译码
reg [7:0] decode;
always @(*) begin
    case (decode_data)
        4'h0: decode = 8'h03;
        4'h1: decode = 8'h9F;
        4'h2: decode = 8'h25;
        4'h3: decode = 8'h0D;
        4'h4: decode = 8'h99;
        4'h5: decode = 8'h49;
        4'h6: decode = 8'h41;
        4'h7: decode = 8'h1F;
        4'h8: decode = 8'h01;
        4'h9: decode = 8'h19;
        4'hA: decode = 8'h11;
        4'hB: decode = 8'hC1;
        4'hC: decode = 8'hE5;
        4'hD: decode = 8'h85;
        4'hE: decode = 8'h61;
        4'hF: decode = 8'h71;
        default: decode = 8'hff;
    endcase
end

//段选信号
always @(posedge clk or posedge rst) begin
    if (rst) begin
        led_cx <= 8'hff;
    end
    else begin
        led_cx <= decode;
    end
end

endmodule