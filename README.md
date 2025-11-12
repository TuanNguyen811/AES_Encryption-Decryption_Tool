# AES File Encryption Tool
![Upload Page](AES_Encryption-Decryption_Tool//%E1%BA%A2nh%20ch%E1%BB%A5p%20m%C3%A0n%20h%C3%ACnh%202025-06-20%20091645.png)

## Giới thiệu

**AES File Encryption Tool** là phần mềm mã hóa và giải mã file/folder sử dụng thuật toán AES với nhiều chế độ (CBC, ECB, CFB, OFB), giúp bảo mật dữ liệu cá nhân hoặc công việc của bạn một cách mạnh mẽ và dễ dàng.

Phần mềm hỗ trợ:
- Mã hóa/giải mã file hoặc cả thư mục.
- Tùy chọn độ dài khóa (128/192/256 bit).
- Lựa chọn mode mã hóa (CBC, ECB, CFB, OFB).
- Hiển thị tiến trình trực tiếp trên giao diện qua progress bar và trạng thái label.
- Tự động phát hiện thông tin file .aes (keysize, mode).
- Tích hợp kiểm tra mật khẩu, xác nhận mật khẩu khi nhập.
- Báo lỗi rõ ràng và thông báo kết quả ngay trên giao diện.

## Tính năng nổi bật

- **Giao diện đơn giản, dễ dùng**: Không cần kiến thức kỹ thuật sâu.
- **Bảo mật mạnh mẽ**: Sử dụng AES chuẩn quốc tế.
- **Tốc độ cao**: Hiển thị thông số thời gian và tốc độ xử lý.
- **Mở rộng dễ dàng**: Hỗ trợ cả file lẫn thư mục, nhiều chế độ mã hóa.
- **Không làm treo ứng dụng**: Quá trình mã hóa/giải mã chạy trên thread riêng, tiến trình cập nhật trực tiếp lên progressBar và label_status.

## Hướng dẫn sử dụng

1. **Chọn file hoặc thư mục** cần mã hóa/giải mã.
2. **Chọn chế độ mã hóa** (mode) và độ dài khóa phù hợp.
3. **Nhập mật khẩu** và xác nhận mật khẩu (khi mã hóa).
4. **Chọn nơi lưu file kết quả**.
5. **Nhấn nút Encrypt/Decrypt** để bắt đầu.
6. Theo dõi tiến trình trên progress bar và trạng thái trên label_status.

## Yêu cầu hệ thống

- Qt 5/6 (đã test với Qt5.15 trở lên)
- C++17 trở lên
- Các thư viện chuẩn: QtCore, QtWidgets, QtConcurrent (nếu dùng), filesystem (C++17)

## Cấu trúc dự án

```
src/
├── mainwindow.h / .cpp
├── successdialog.h / .cpp / .ui
├── encryptworker.h / .cpp
├── decryptworker.h / .cpp
├── aes.h / .cpp
├── hash.h / .cpp
├── compressor.h / .cpp
├── ... (các file hỗ trợ khác)
resources/
├── icons/
```
- **mainwindow.cpp**: Điều phối giao diện, cập nhật tiến trình, xử lý sự kiện.
- **successdialog**: Thông báo thành công (có thể không dùng nếu hiển thị bằng label_status).
- **encryptworker/decryptworker**: Xử lý mã hóa/giải mã ở thread riêng, phát tín hiệu cập nhật tiến trình.
- **label_status, progressBar**: Hiển thị trạng thái và tiến trình trực tiếp.

## Đóng góp & phát triển

- Fork, tạo nhánh mới và gửi Pull Request nếu bạn muốn đóng góp.
- Báo lỗi, đề xuất tính năng qua Issues.

## License

MIT License

---
**Dự án dành cho cá nhân, học tập và ứng dụng thực tế.**
