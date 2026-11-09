`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/07 15:54:48
// Design Name: 
// Module Name: testbench
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module testbench();

reg rst;
reg clk;
wire uart_rx;

initial begin
    clk = 1'b0;
    rst = 1'b1;
    
    #10;

    // 复位
    rst = 1'b0;
    #500000000 $finish;
end
always #5 clk = ~clk;   //生成时钟

StateMachine u_statemachine (.clk(clk),.rst(rst),.uart_tx(uart_rx));
endmodule
