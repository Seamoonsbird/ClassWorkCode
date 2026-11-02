`timescale 1ns / 1ps
module reg8file (
    input  wire clk,  
    input  wire clr,    
    input  wire en,
    input  wire [7:0] d,
    input  wire [2:0] wsel,
    input  wire [2:0] rsel,
    output reg  [7:0] q    
);
/*
clk：时钟信号，连接Y18（Minisys）或P17（EGO1）管脚，时钟频率100MHz
clr：异步复位信号，高电平有效，复位时8个寄存器都清零，接按键开关S1
en：同步使能，此处也叫写使能，高电平有效进行数据写操作，自选拨码开关连接
wsel[2:0]：写选择信号，选择将输入写入哪个寄存器，自选拨码开关连接
rsel[2:0]：读选择信号，选择读取哪个寄存器输出，自选拨码开关连接。读操作是异步逻辑，读选择编号改变输出跟着变，无需与时钟边沿同步
d[7:0]：输入数据，自选拨码开关连接，用EGO1建议接DIP开关方便操作
q[7:0]：输出数据，自选LED灯连接显示
*/
reg [7:0] regfile [7:0];
integer i;
always @(posedge clk or posedge clr) begin
    if (clr)begin
        for (i = 0; i < 8; i = i + 1)begin
            regfile[i] <= 8'b0;
        end
    end
    else if (en)begin
        regfile[wsel] <= d;
    end
end

always @(*) begin
    q = regfile[rsel];
end
endmodule
