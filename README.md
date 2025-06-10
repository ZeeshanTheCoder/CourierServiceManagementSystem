
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

## 🛠️ How to Run the Project

### ▶️ On Microsoft Visual Studio 2022

1. **Clone this repository**:
   ```
   https://github.com/ZeeshanTheCoder/CourierServiceManagementSystem.git
   ```

2. **Open Visual Studio**:
   - Go to `File` → `Clone Repository`, and paste the URL above.

3. **Create a new Console App project**:
   - `File` → `New` → `Project` → Select `Console App` (C++) → Click `Create`.

4. **Add source files**:
   - Right-click `Source Files` → `Add` → `Existing Item` → Select `.cpp` files from the cloned repo.

5. **Build & Run**:
   - Press `Ctrl + F5` or click `Start Without Debugging`.

---

### ▶️ On Dev C++

1. **Download or Clone the repository**:
   - Download ZIP or use:
     ```
     git clone https://github.com/ZeeshanTheCoder/CourierServiceManagementSystem.git
     ```

2. **Open Dev C++** and create new Console App project.

3. **Replace main file** with your code:
   - Remove auto-generated code and paste your full `main.cpp` contents or include external files.

4. **Save, Compile & Run**:
   - Click `Execute` → `Compile & Run` or press `F11`.

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
