1.1 
 1.1.1 CISC(complex Instruction Set Computer) 
+ Là kiến trúc máy tính với tập lệnh phức tạp. Mỗi tập lệnh có thể thực hiện nhiều thao tác cấp thấp (như nạp dữ liệu, tính toán, lưu kết quả) chỉ trong một instruction. Kiến trúc này thường có hàng trăm lệnh, một số lệnh rất phức tạp nhưng ít được sử dụng. Ví dụ như là x86 (intel, AMD). 
 1.1.2 RISC (Reduced Instruction Set Computer):
+ Là kiến trúc máy tính với tập lệnh rút gọn, chỉ gồm những lệnh đơn giản, cố định độ dài. Mỗi lệnh chỉ thực hiện một thao tác rất cơ bản. concept chính của RISC là đơn giản hóa phần cứng, tối ưu pipeline và tăng tốc độ xử lý. Ví dụ điển hình là ARM, MIPS, RISC-V.
2 Ưu điểm và nhược điểm của CISC và RISC
2.1 CISC 
2.1.1 Ưu điểm: 
   + Chương trình ngắn hơn (ít lệnh hơn)
   + Dễ lập trình ở mức Assembly 
   + Phù hợp với ứng dụng phức tạp trên PC, Server
2.1.2 Nhược điểm: 
   + Lệnh dài, độ dài thay đổi → khó decode.
   + Phần cứng phức tạp, tiêu thụ năng lượng lớn 
   + Pipeline khó tối ưu
2.2. RISC
2.2.1 Ưu điểm: 
   + Lệnh ngắn, cố định → dễ giải mã, tốc độ cao.
   + Pipeline hiệu quả, dễ song song hóa. 
   + Phần cứng đơn giản, tiết kiệm năng lượng
2.2.2 Nhược điểm: 
   + Cần nhiều lệnh hơn để hoàn thành cùng một công việc → chương trình dài hơn.
   + Yêu cầu compiler thông minh để tối ưu.
3. So sánh CISC và RISC theo các tiêu chí.
+ Cấu trúc tập lệnh.
- CISC: Nhiều, phức tạp, độ dài thay đổi
- RISC: ít, đơn giản, độ dài cố định
+ Tốc độ sử lý.
- CISC: Chậm hơn do mỗi lệnh cần nhiều chu kỳ
- RISC: Nhanh hơn, 1 lệnh ≈ 1 chu kỳ
+ Kích thước chương trình.
- CISC: Ngắn hơn (ít lệnh hơn)
- RISC: Dài hơn (nhiều lệnh hơn)
+ Ứng dụng thực tế.
- CISC: PC, laptop, server (Intel, AMD).
- RISC: Smartphone, IoT, nhúng (ARM, RISC-V).