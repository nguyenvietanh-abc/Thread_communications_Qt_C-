Thread_Communication là quá trình trao đổi dữ liệu hoặc tín hiệu giữa các thread (luồng) trong cùng 1 process (tiến trình). Các thread trong cùng 1 process chia sẻ chung không gian bộ nhớ riêng (shared address space), và giao tiếp giữa các thread thông thường là nhanh, nhưng phức tạp hơn để "đồng bộ hóa".

Trong library_oop TC dùng để tách biệt các tác vụ khỏi main thread (chạy vòng lặp console) phòng tránh treo console. Gửi yêu cầu từ Main Thread tới Worker Thread để nhận result hoặc progress từ WT về MT hiển thị console.

Đặc điểm của giao tiếp đa luồng:
+ Shared address space 
+ Thread-Safe Requirement: do shared memory nên Cần cơ chế đồng bộ hóa như lock, mutex, signal - slot (Qt) để tránh race condition khi multi thread cùng truy cập 1 dữ liệu.
+Cơ chế giao tiếp: chọn Safe-Tread

>> Sự khác biệt chính giữa Thread - Communications với IPC (Inter process communications) ở chỗ IPC cho phép đa tiến trình (multi processes) trong hệ điều hành có thể trao đổi dữ liệu or tín hiệu với nhau. 

IPC: Mỗi process là một chương trình đang chạy mang không gian bộ nhớ riêng (reparate adress space) != shared address space trong TC. Ví dụ như 2 client với 1 server. 
