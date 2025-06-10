
# Courier Service Management System

A C++ based console application developed by [ZeeshanTheCoder](https://github.com/ZeeshanTheCoder), designed to manage courier services efficiently. The system supports user registration, parcel booking, courier assignments, and status tracking for a complete end-to-end delivery workflow.

---

## 🚀 Features

### 👤 User Panel
- Register & Login
- Book new parcels (Normal or Express delivery)
- Track parcel status by tracking ID
- View all booked parcels
- Cancel parcels (if status is pending)
- Export parcel records to CSV

### 🚚 Courier Panel
- Login with courier role
- View assigned parcels
- Update parcel status (In Transit / Out for Delivery / Delivered)
- View delivery history
- Export assigned deliveries to CSV

### 🛠️ Admin Panel
- View all parcels in the system
- Update any parcel's status
- Assign couriers to parcels
- Export all parcel records to CSV
- View all registered users and couriers

---

## 💻 Technologies Used
- C++ (Standard Library)
- File Handling (`fstream`)
- Time & Date Formatting (`ctime`, `iomanip`)
- Console-based User Interface

---

## 📁 Folder Structure

```
CourierServiceManagementSystem/
│
├── main.cpp              // Source code
├── users.txt             // Stores registered users
├── parcels.txt           // Stores parcel data
├── README.md             // Project documentation
└── *.csv                 // Exported data files
```

---

## 📝 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/ZeeshanTheCoder/CourierServiceManagementSystem.git
   ```
2. Move into the project folder:
   ```bash
   cd CourierServiceManagementSystem
   ```
3. Compile the project:
   ```bash
   g++ main.cpp -o courier
   ```
4. Run the program:
   ```bash
   ./courier
   ```

---

## 📦 Future Enhancements

- Generate unique alphanumeric tracking IDs
- Add password protection and hashing
- Split into multiple source/header files for modularity
- GUI version using Qt or other library

---

## 📄 License

This project is licensed under the MIT License.  
Feel free to fork, contribute, or use it for educational purposes!

---

**Made with 💻 by [ZeeshanTheCoder](https://github.com/ZeeshanTheCoder)**
