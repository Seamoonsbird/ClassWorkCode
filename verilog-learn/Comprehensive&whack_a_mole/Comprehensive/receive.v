`timescale 1ns / 1ps

module receive(
    input wire clk,
    input wire rst,
    input wire uart_rx,

    output reg [2:0] count,
    output reg [23:0] dout
    );

// 先实例化一个串口接收模块
wire [7:0] data;
wire valid;
uart_recv u_uart_recv(
    .clk(clk),
    .rst(rst),
    .din(uart_rx),
    .valid(valid),
    .data(data)
);

// 计算收到的位数count
always @(posedge clk or posedge rst) begin
    if (rst) begin
        count <= 3'b0;
    end
    else if (valid && count < 3'd6) begin
        count <= count + 3'b1;
    end
    else begin
        count <= count;
    end
end

// 解码收到的数据
reg [3:0] decode_data;
always @(*) begin
    case (data)
        // '0' ~ '9'
        8'h30: decode_data = 4'h0;
        8'h31: decode_data = 4'h1;
        8'h32: decode_data = 4'h2;
        8'h33: decode_data = 4'h3;
        8'h34: decode_data = 4'h4;
        8'h35: decode_data = 4'h5;
        8'h36: decode_data = 4'h6;
        8'h37: decode_data = 4'h7;
        8'h38: decode_data = 4'h8;
        8'h39: decode_data = 4'h9;
        // 'A' ~ 'F' / 'a' ~ 'f'
        8'h41, 8'h61: decode_data = 4'hA;
        8'h42, 8'h62: decode_data = 4'hB;
        8'h43, 8'h63: decode_data = 4'hC;
        8'h44, 8'h64: decode_data = 4'hD;
        8'h45, 8'h65: decode_data = 4'hE;
        8'h46, 8'h66: decode_data = 4'hF;
        default:      decode_data = 4'h0;
    endcase
end

// 更新data
always @(posedge clk or posedge rst) begin
    if (rst) begin
        dout <= 24'h000000;
    end
    else if (valid) begin
        dout <= {dout[19:0],decode_data};
    end
end

endmodule
