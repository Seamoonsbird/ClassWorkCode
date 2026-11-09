`timescale 1ns / 1ps

module StateMachine(
    input wire clk,
    input wire rst,
    output wire uart_tx
    );

    // 发送的数据
    reg [3:0] data_inx;
    reg [7:0] send_data;
    localparam DATA_INX_MAX = 4'd14;
    always @(*) begin
        case (data_inx)
            4'd0 : send_data = "h";
            4'd1 : send_data = "i";
            4'd2 : send_data = "t";
            4'd3 : send_data = "s";
            4'd4 : send_data = "z";
            4'd5 : send_data = "2";
            4'd6 : send_data = "0";
            4'd7 : send_data = "2";
            4'd8 : send_data = "5";
            4'd9 : send_data = "3";
            4'd10 : send_data = "1";
            4'd11 : send_data = "0";
            4'd12 : send_data = "4";
            4'd13 : send_data = "1";
            4'd14 : send_data = "7";
            default: send_data = "!";
        endcase
    end


    // 实例化一个计数器，用于间隔0.30000000s发送不同行
    localparam CNT_LINE_MAX = 25'd30000000-1;
    wire [24:0] cnt_line;
    counter #(.CNT_MAX(CNT_LINE_MAX)) u_counter_1(
        .clk(clk),
        .rst(rst),
        .pause(1'b0),
        .one(1'b0),
        .reboot(1'b0),
        .cnt(cnt_line)
    );

    // 实例化一个计数器，用于间隔0.00500000s发送不同字符
    localparam CNT_LETTER_MAX = 19'd500000-1;
    wire [24:0] cnt_letter;
    counter #(.CNT_MAX(CNT_LETTER_MAX)) u_counter_2(
        .clk(clk),
        .rst(rst),
        .pause(1'b0),
        .one(1'b0),
        .reboot(cnt_line == CNT_LINE_MAX),
        .cnt(cnt_letter)
    );

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            data_inx <= 3'b0; // 暂定先是0
        end
        else if ((cnt_letter == CNT_LETTER_MAX) && (data_inx <= DATA_INX_MAX) && (cnt_line < CNT_LINE_MAX)) begin
            data_inx <= data_inx + 1;
        end
        else if (cnt_line == CNT_LINE_MAX) begin
            data_inx <= 3'b0;
        end
        else if (data_inx > DATA_INX_MAX) begin
            data_inx <= data_inx;
        end
    end

    reg valid;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            valid <= 1'b0;
        end
        else if((cnt_letter == CNT_LETTER_MAX) && (data_inx < DATA_INX_MAX)) begin
            valid <= 1'b1;
        end
        else if(cnt_line == CNT_LINE_MAX) begin
            valid <= 1'b1;
        end
        else begin
            valid <= 1'b0;
        end
    end

    // 实例化一个串口发送模块
    uart_send u_uart_send (
        .clk(clk),
        .rst(rst),
        .valid(valid),
        .data(send_data),
        .dout(uart_tx)
    );

endmodule
