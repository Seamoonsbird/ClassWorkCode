`timescale 1ns / 1ps

module testbench();

reg clk;
reg clr;
reg en;
reg [7:0] d;
reg [2:0] wsel;
reg [2:0] rsel;
wire [7:0] q;

initial begin
    //初始复位
    clk = 1'b0;
    clr = 1'b1;
    en = 1'b0;
    d = 8'b0;
    wsel = 3'b0;
    rsel = 3'b0;
    #10;

    //往001寄存器写数据
    clr = 1'b0;
    en = 1'b1;
    d = 8'h0c;
    wsel = 3'b001;
    #10;

    //从001寄存器读数据
    en = 1'b0;
    rsel = 3'b001;
    #10;

    //再往010寄存器写数据
    en = 1'b1;
    wsel = 3'b010;
    d = 8'h0f;
    #10;

    //再往101寄存器写数据
    wsel = 3'b101;
    d = 8'he;
    #10;

    //从101寄存器读数据
    en = 1'b0;
    rsel = 3'b101;
    #10;

    //从010寄存器读数据
    rsel = 3'b010;
    #10;

    clr = 1'b1;
    #10 $finish;

end

always #5 clk = ~clk;   //生成时钟

reg8file u_reg8file(
    .clk(clk),
    .clr(clr),
    .en(en),
    .d(d),
    .wsel(wsel),
    .rsel(rsel),
    .q(q)
);


endmodule
