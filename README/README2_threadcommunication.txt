Thread_Communication là quá trình trao đổi dữ liệu hoặc tín hiệu giữa các thread (luồng) trong cùng 1 process (tiến trình). Các thread trong cùng 1 process chia sẻ chung không gian bộ nhớ riêng (shared address space), và giao tiếp giữa các thread thông thường là nhanh, nhưng phức tạp hơn để "đồng bộ hóa".

Trong library_oop TC dùng để tách biệt các tác vụ khỏi main thread (chạy vòng lặp console) phòng tránh treo console. Gửi yêu cầu từ Main Thread tới Worker Thread để nhận result hoặc progress từ WT về MT hiển thị console.

Đặc điểm của giao tiếp đa luồng:
+ Shared address space 
+ Thread-Safe Requirement: do shared memory nên Cần cơ chế đồng bộ hóa như lock, mutex, signal - slot (Qt) để tránh race condition khi multi thread cùng truy cập 1 dữ liệu.
+Cơ chế giao tiếp: chọn Safe-Tread

