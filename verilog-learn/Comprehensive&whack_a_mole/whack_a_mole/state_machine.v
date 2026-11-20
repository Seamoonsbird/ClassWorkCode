`timescale 1ns / 1ps

module state_machine(
    input wire clk,
    input wire rst,
    input wire start,
    input wire [7:0] count_time,
    input wire uart_rx,
    input wire silent,

    output reg [23:0] dis,
    output reg [2:0] dis_able,
    output wire buzzer,
    output reg reboot
    );

reg [1:0] current_state;
reg [1:0] next_state;

reg [3:0] random_count;

localparam IDLE = 2'b00;   // 空闲态
localparam GAME = 2'b01;   // 游戏态
localparam FINISH  = 2'b10;   // 结束态

// 先实例化一个串口接收模块
wire [7:0] data; // 原始十六进制ASCII码
wire valid;
uart_recv u_uart_recv(
    .clk(clk),
    .rst(rst),
    .din(uart_rx),
    .valid(valid),
    .data(data)
);

// 解码收到的数据
reg [3:0] decode_data; // 已经解码的数据
always @(*) begin
    case (data)
        // '0' ~ '9'
        8'h30: decode_data = 4'h0;
        8'h31: decode_data = 4'h1;
        8'h32: decode_data = 4'h2;
        8'h33: decode_data = 4'h3;
        8'h34: decode_data = 4'h4;
        8'h35: decode_data = 4'h5;
        8'h36: decode_data = 4'h6;
        8'h37: decode_data = 4'h7;
        8'h38: decode_data = 4'h8;
        8'h39: decode_data = 4'h9;
        default:      decode_data = 3'h0;
    endcase
end

// 生成随机数
reg random_sig;
reg [7:0] random_count_unable;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        random_count_unable <= 8'b10100101;
    end
    else begin
        random_count_unable <= {random_count_unable[6:0],(random_count_unable[3]^random_count_unable[4]^random_count_unable[5]^random_count_unable[7])};
    end
end




// 对start进行上升沿检测
reg sig_r0;
reg sig_r1;

always @(posedge clk or posedge rst) begin
    if (rst)begin
        sig_r0 <= 1'b0;
        sig_r1 <= 1'b0;
    end
    else begin
        sig_r0 <= start;
        sig_r1 <= sig_r0;
    end
end

wire start_pos_edge = ~sig_r1 & sig_r0;


// 实例化一个音乐模块
reg [2:0] music_code;
music U_music(
    .clk(clk),
    .rst(rst),
    .music_code(music_code),
    .silent(silent),
    .buzzer(buzzer)
);

// 实例化一个计数器，用于计算播放成功音效的时长
// 0.40000000s
localparam SUCCESSED_MUSIC_TIME = 29'd40000000-1;
wire [28:0]successed_music_time;
counter #(.CNT_MAX(SUCCESSED_MUSIC_TIME)) u_counter_6(
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b1),
    .reboot((valid && (random_count == decode_data))),
    .auto_start(1'b0),
    .cnt(successed_music_time)
);

// 实例化一个计数器，用于计算播放完成音效的时长
// 3.00000000s
localparam FINISH_MUSIC_TIME = 29'd300000000-1;
wire [28:0]finish_music_time;
counter #(.CNT_MAX(FINISH_MUSIC_TIME)) u_counter_7(
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b1),
    .reboot(((next_state == FINISH)&&(current_state == GAME))),
    .auto_start(1'b0),
    .cnt(finish_music_time)
);
//reboot一定要(next_state == FINISH)&&(current_state == GAME)不然会一直清零重启

// 成功记号
wire suceessed_sig = (successed_music_time > 0);
// 失败记号
reg failed_sig;
// 完成记号
wire finish_sig = (finish_music_time > 0);

// 需要生成的信号
always @(posedge clk or posedge rst) begin
    if (rst) begin
        random_sig <= 1'b0;
    end
    else if ((start || (valid && (random_count == decode_data))) && (random_sig == 1'b0)) begin
        random_sig <= 1'b1;
    end
    else if (random_sig) begin
        random_sig <= 1'b0;
    end
end

// 对生成的随机数进行保存并且显示
always @(posedge clk or posedge rst) begin
    if (rst) begin
        random_count <= 3'b0;
    end
    else if (random_sig && (current_state == GAME)) begin
        random_count <= random_count_unable % 10;
    end
    else begin
        random_count <= random_count;
    end
end

always @(posedge clk or posedge rst) begin
    if (rst) begin
        dis_able <= 3'd0;
    end
    else if (start) begin
        dis_able <=3'd1;
    end
    else begin
        dis_able <= dis_able;
    end
end

reg [6:0] successed_count;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        successed_count <= 7'b0;
    end
    else if (reboot) begin
        successed_count <= 7'b0;
    end
    else if ((valid && (random_count == decode_data))&&(current_state==GAME)) begin
        successed_count <= successed_count + 1;
    end
    else begin
        successed_count <= successed_count;
    end
end


wire [3:0] random_count_one = random_count % 5'd10;
wire [3:0] successed_count_ten = successed_count / 5'd10;
wire [3:0] successed_count_one = successed_count % 5'd10;
always @(*) begin
    dis = {8'h0, random_count_one,4'h0,successed_count_ten,successed_count_one};
end

// 对失败信号进行赋值
always @(posedge clk or posedge rst) begin
    if (rst) begin
        failed_sig <= 1'b0;
    end
    else if (valid && (random_count != decode_data)) begin
        failed_sig <= 1'b1;
    end
    else if (suceessed_sig) begin
        failed_sig <= 1'b0;
    end
    else begin
        failed_sig <= failed_sig;
    end
end






// 第1个always块，描述次态迁移到现态
always @(posedge clk or posedge rst) begin
    if(rst)  current_state <= IDLE;
    else     current_state <= next_state;
end

// 第2个always块，描述状态转移条件判断
always @(*) begin
    case (current_state)
        IDLE : 
            if (start_pos_edge) begin
                next_state = GAME;
            end
            else begin
                next_state = IDLE;
            end
        GAME :
            // 一定要用reboot == 1'b0，否则会出现reboot变成1但是倒计时传过来的还是0（下一拍才变）
            // 导致又进入finish，如果加上reboot=0就可以解决这一拍的矛盾了
            if ((count_time == 8'h0)&&(reboot == 1'b0)) begin
                next_state = FINISH;
            end
            else begin
                next_state = GAME;
            end
        FINISH :
            if (start_pos_edge) begin
                next_state = GAME;
            end
            else begin
                next_state = FINISH;
            end
        default: next_state = IDLE;
    endcase
end

// 第3个always块，描述输出逻辑

// 产生music_code
localparam IDLE_MUSIC = 3'b00; // 空闲态，不发声
localparam START_MUSIC = 3'b01; // 开始游戏声音
localparam SUCCESSED_MUSIC = 3'b10; // 成功声音
localparam FAILED_MUSIC = 3'b11; // 失败声音
localparam NO_MUSIC = 3'b100; // 没有声音
localparam FINISHED_MUSIC = 3'b101; // 结束音乐

always @(posedge clk or posedge rst) begin
    if (rst) begin
        music_code <= IDLE_MUSIC;
    end
    else begin
        if (current_state == IDLE) begin
            music_code <= IDLE_MUSIC;
        end
        else if ((current_state == GAME) && (failed_sig == 1'b1)) begin
            music_code <= FAILED_MUSIC;
        end
        else if ((current_state == GAME) && (suceessed_sig == 1'b0)&&(failed_sig == 1'b0)) begin
            music_code <= START_MUSIC;
        end
        else if ((current_state == GAME) && (suceessed_sig == 1'b1)) begin
            music_code <= SUCCESSED_MUSIC;
        end
        else if ((current_state == FINISH) && finish_sig) begin
            music_code <= FINISHED_MUSIC;
        end
        else if ((current_state == FINISH) && (finish_sig == 1'b0)) begin
            music_code <= NO_MUSIC;
        end
        else begin
            music_code <= NO_MUSIC;
        end
    end
end

always @(posedge clk or posedge rst) begin
    if (rst) begin
        reboot <= 1'b0;
    end
    else if ((reboot == 1'b0) && ((current_state == FINISH)&&(next_state == GAME))) begin
        reboot <= 1'b1;
    end
    else begin
        reboot <= 1'b0;
    end
end
endmodule
