`timescale 1ns / 1ps

module testbench();

reg clk;  //接Y18
reg rst;    //接按键开关S1
reg freq_ctrl; //0是500Hz, 1是10Hz
reg dir_ctrl; //0是左移, 1是右移
reg mode_sel; //0是1个灯亮, 1是两个灯亮
wire  [7:0] led;

//仿真使用时间间隔为0.000000020s和0.000000040s

initial begin
    //初始复位
    clk = 1'b0;
    rst = 1'b1;
    freq_ctrl = 1'b0;
    dir_ctrl = 1'b0;
    mode_sel = 1'b0;
    #10;

    //复位信号
    rst = 1'b0;
    #960;

    //调整频率
    freq_ctrl = 1'b1;
    #480;

    //调整模式
    mode_sel = 1'b1;
    #480;

    //按下复位键
    rst = 1'b1;
    #10;

    //松开复位键
    rst = 1'b0;
    #480 $finish;

end

always #5 clk = ~clk;   //生成时钟

flowing_water_lights #(.CNT_BIG(24'd6), .CNT_SMALL(24'd11)) u_flowing_water_lights(
    .clk(clk),
    .rst(rst),
    .freq_ctrl(freq_ctrl),
    .dir_ctrl(dir_ctrl),
    .mode_sel(mode_sel),
    .led(led)
);

endmodule
