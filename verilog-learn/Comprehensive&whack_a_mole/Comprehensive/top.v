`timescale 1ns / 1ps

module top(
    input wire clk,        
    input wire rst,
    input wire uart_rx,
    input wire btn,

    output wire [7:0]  led_en,   // 位选信号
    output wire [7:0]  led_cx,    // 段选信号
    output wire uart_tx
    );

// 实例化一个接收模块
wire [2:0] count;
wire [23:0] dout;
receive u_receive(
    .clk(clk),
    .rst(rst),
    .uart_rx(uart_rx),
    .count(count),
    .dout(dout)
);

// 实例化一个发送模块
wire [7:0] cnt;
send #(.DEBOUNCE_TIME(24'd2000000 - 1)) u_send (
    .clk(clk),
    .rst(rst),
    .btn(btn),
    .uart_tx(uart_tx),
    .cnt(cnt)
);

// 实例化一个显示模块
led_ctrl_unit #(.CNT_MAX(24'd200000-1)) u_led_ctrl_unit(
    .clk(clk),
    .rst(rst),
    .display({cnt,dout}),
    .dis_max(count),
    .led_en(led_en),
    .led_cx(led_cx)
);

endmodule
