`timescale 1ns / 1ps
module dff (
    input      clk,
    input      clr,
    input      en ,
    input      d  ,
    output reg q
);
/*
clr：异步复位信号，高电平有效，接按键开关S1，按下输入为1，只需按一次，不用一直按
en：同步使能，高电平有效，接拨码开关SW7，往上拨为1
d：输入数据，接拨码开关SW0
q：输出数据，接右侧的GLD0或LD2_0
*/
always @(posedge clk or posedge clr) begin
    if (clr == 1)begin
        q <= 1'b0;
    end
    else if (en == 1)begin
        q <= d;
    end
    else begin
        q <= q;
    end
end
endmodule