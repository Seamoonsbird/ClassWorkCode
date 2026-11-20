`timescale 1ns / 1ps

module top(
    input wire clk,
    input wire rst,
    input wire uart_rx,
    input wire start_btn,
    input wire silent,

    output wire [7:0]  led_en,   // 位选信号
    output wire [7:0]  led_cx,   // 段选信号
    output wire buzzer           // 蜂鸣器
    );

    // 实例化一个倒计时模块
    wire reboot;
    wire [7:0] count;
    time_counter u_time_counter(
        .clk(clk),
        .rst(rst),
        .start(start_btn),
        .count(count),
        .reboot(reboot)
    );

    // 将倒计时连接到数码管
    // 实例化一个显示模块
    wire [23:0] random_count;
    wire [2:0] dis_able;
    led_ctrl_unit #(.CNT_MAX(24'd200000-1)) u_led_ctrl_unit(
        .clk(clk),
        .rst(rst),
        .display({count,random_count}),
        .dis_able(dis_able),
        .led_en(led_en),
        .led_cx(led_cx)
    );    



    // 实例化一个状态机
    state_machine state_machine(
        .clk(clk),
        .rst(rst),
        .start(start_btn),
        .count_time(count),
        .uart_rx(uart_rx),
        .dis(random_count),
        .dis_able(dis_able),
        .silent(silent),
        .buzzer(buzzer),
        .reboot(reboot)
        );


endmodule
