`timescale 1ns / 1ps

module top_tb();
reg rst;
reg clk;
reg btn;
reg uart_rx;

wire [7:0] led_en;
wire [7:0] led_cx;
wire uart_tx;

initial begin
    clk = 1'b0;
    rst = 1'b1;
    btn = 1'b0;
    uart_rx = 1'b0;
    #10;

    // 复位
    rst = 1'b0;
    #10000000;
    btn = 1'b1;
    #20000000;
    btn = 1'b0;
    #10000000;
    btn = 1'b1;
    #20000000;
    btn = 1'b0;

    #500000000 $finish;
end
always #5 clk = ~clk;   //生成时钟

top u_top (.clk(clk),.rst(rst),.uart_rx(uart_rx),.btn(btn),.led_en(led_en),.led_cx(led_cx),.uart_tx(uart_tx));
endmodule
