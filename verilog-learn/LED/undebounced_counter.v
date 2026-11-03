`timescale 1ns / 1ps

module undebounced_counter(
    input wire clk,
    input wire rst,
    input wire key_in,
    output reg [7:0] cnt
);
    // // 测试
    // always @(*) begin
    //     if (key_in)begin
    //         cnt = 8'h88;
    //     end
    //     else begin
    //         cnt = 8'h66;
    //     end
    // end

    //边沿检测
    reg sig_r0;
    reg sig_r1;

    always @(posedge clk or posedge rst) begin
        if (rst)begin
            sig_r0 <= 1'b0;
            sig_r1 <= 1'b0;
        end
        else begin
            sig_r0 <= key_in;
            sig_r1 <= sig_r0;
        end
    end

    wire pos_edge = ~sig_r1 & sig_r0;


    reg [6:0] count;

    always @(posedge clk or posedge rst) begin
        if (rst)begin
            count <= 2'd0;
        end
        else begin
            if (pos_edge)begin
                if (count < 99)begin
                    count <= count + 1;
                end
                else begin
                    count <= 2'd0;
                end
            end
        end
    end


    wire [3:0] count_ten = count / 7'd10;
    wire [3:0] count_one = count % 7'd10;
    always @(*) begin
        cnt = {count_ten, count_one};
    end

endmodule