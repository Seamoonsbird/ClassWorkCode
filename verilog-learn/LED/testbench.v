`timescale 1ns / 1ps

module testbench();

reg rst;
reg clk;
reg change_task;
reg counter_key;
reg counter_0_20_key;

wire [7:0] led_en;
wire [7:0] led_cx;

initial begin
    clk = 1'b0;
    rst = 1'b1;
    change_task = 1'b1;
    counter_key = 1'b0;
    counter_0_20_key = 1'b0;
    #10;

    // 复位
    rst = 1'b0;
    #1000;

    // 切换任务
    change_task = 1'b0;
    #1000;

    // 制造抖动效果1
    counter_key = 1'b1;
    #20;
    counter_key = 1'b0;
    #20;
    counter_key = 1'b1;
    #40;
    counter_key = 1'b0;
    #40;
    counter_key = 1'b1;
    #120;
    counter_key = 1'b0;
    #200;

    // 制造抖动效果2
    counter_key = 1'b1;
    #80;
    counter_key = 1'b0;
    #20;
    counter_key = 1'b1;
    #20;
    counter_key = 1'b0;
    #40;
    counter_key = 1'b1;
    #120;
    counter_key = 1'b0;
    #200;

    // 边沿检测
    counter_key = 1'b1;
    #30;
    counter_key = 1'b0;
    #200;


    #1000 $finish;

end


always #5 clk = ~clk;   //生成时钟

//仿真时间调整
//数码管使用100ns，即0.00000010s
//消抖时间使用100ns，即0.00000010s
//计数器自增时间使用1000ns，即0.00000100s
LED #(24'd10-1, 24'd10-1, 24'd100-1) u_LED(
    .clk(clk),
    .rst(rst),
    .change_task(change_task),
    .counter_key(counter_key),
    .counter_0_20_key(counter_0_20_key),

    .led_en(led_en),
    .led_cx(led_cx)
);

endmodule
