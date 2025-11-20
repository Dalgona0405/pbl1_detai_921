# 🏗️ Material Management System (Ứng dụng Quản lý Vật tư)

> **PBL1 - Project Based Learning 1**
> **Topic:** Application for Material Management using C Language.

## 📖 Introduction (Giới thiệu)
This project is a console-based application designed to manage construction materials. It was developed as part of the PBL1 course at **Danang University of Science and Technology (DUT)**.

The system allows users to manage material details (ID, Name, Type, Quantity, Price, etc.) efficiently using **Doubly Linked List** data structure to ensure dynamic memory optimization.

## 🚀 Features (Chức năng)
Based on the project requirements, the application includes:
* **Manage Materials:** Add, Insert, and Delete materials.
* **Advanced Search:** Find materials by ID, Name, Type, or Manufacturer.
* **Sorting:** Sort list by Quantity, Unit Price, or Total Amount (Bubble Sort algorithm).
* **Auto-calculation:** Automatically calculate "Total Amount" based on Quantity and Price.
* **Special Delete:** Function to bulk delete items with Quantity > 100.
* **File I/O:** Load initial data from `Vat_tu.txt` and save changes to `Vat_tu_moi.txt`.
* **Statistics:** Generate reports by Material Type.

## 🛠️ Technical Details (Kỹ thuật sử dụng)
* **Language:** C
* **Data Structure:** Doubly Linked List (Danh sách liên kết đôi).
* **Algorithms:**
    * Linear Search (O(n)).
    * Bubble Sort (O(n^2)).
* **IDE:** Dev-C++ / VS Code.

## 📸 Screenshots
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 224508" src="https://github.com/user-attachments/assets/1fef1f6e-e239-4719-817d-381882ff5062" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 224634" src="https://github.com/user-attachments/assets/c33a1109-9286-4fef-a21a-6dfa01605bc2" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 225537" src="https://github.com/user-attachments/assets/6eddae97-32c2-496d-96da-90d152a5a3cd" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 230222" src="https://github.com/user-attachments/assets/f91ee04a-9036-4c9d-b36d-31af03e124f1" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 231547" src="https://github.com/user-attachments/assets/b7877429-6e50-4a88-82e7-98ef6b6d42f9" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 231940" src="https://github.com/user-attachments/assets/0bdf2ecb-1be9-4004-91f4-481aeb7486ba" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 232833" src="https://github.com/user-attachments/assets/36550d45-911c-42d0-bbc8-1e13df3793f7" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 232852" src="https://github.com/user-attachments/assets/08dac14e-9b7e-4515-970a-824b9b924160" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 233522" src="https://github.com/user-attachments/assets/b6da0cd7-bcad-4bc1-a106-8157ff319cc6" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-15 235912" src="https://github.com/user-attachments/assets/7076c8f5-7106-4aef-abf2-9b275050181d" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-16 004708" src="https://github.com/user-attachments/assets/c6176cd4-6733-445a-b3c0-39bfb78d172d" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-16 005238" src="https://github.com/user-attachments/assets/8fba3234-6f9e-42ce-8177-0131a41013b3" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-16 011101" src="https://github.com/user-attachments/assets/dbfd9e9b-bfbf-47f4-84d6-d38afb68768f" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-16 011728" src="https://github.com/user-attachments/assets/9126cc2a-cc59-4445-a9c0-9c45788ba55c" />
<img width="1920" height="1020" alt="Ảnh chụp màn hình 2025-06-16 012711" src="https://github.com/user-attachments/assets/be7a8d78-f26f-498f-bf2a-4d984475160f" />
<img width="1920" height="1021" alt="Ảnh chụp màn hình 2025-06-16 013308" src="https://github.com/user-attachments/assets/7de35379-d715-4526-a283-61ac7e899eec" />
<img width="1920" height="1021" alt="Ảnh chụp màn hình 2025-06-16 013608" src="https://github.com/user-attachments/assets/39d7d299-fb02-45d0-8eb8-d907e1bbdf1f" />
<img width="1920" height="1021" alt="Ảnh chụp màn hình 2025-06-16 014748" src="https://github.com/user-attachments/assets/e98a3248-e3f2-4c99-8e73-e64d0a46089a" />


## 👥 Authors
* **Bui An Binh**
* **Thi Nguyen Thanh Truc**
* *Instructor:* MSc. Do Thi Tuyet Hoa.

## 📝 Usage
1. Clone the repo.
2. Compile the `Quanlivattu.c` file using a C compiler (GCC).
3. Ensure `Vat_tu.txt` is in the same directory as the executable.
4. Run the program.
