# E-commerce Platform

🚀 This project is a **modular e-commerce platform** designed to manage users, products, browsing history, and provide personalized product recommendations using a **graph-based recommendation system**.

## 📌 Features
### 🔹 User & Product Management
- Efficient storage using **hash tables** to ensure quick access and modification.
- Users and products are handled using **linked lists** at each hash table index to resolve collisions.

### 🔹 Browsing & Purchase History Tracking
- Interaction data is stored in an **adjacency matrix**, where:
  - `1` represents a **browsing action**.
  - `2` represents a **purchase action**.
- A **weights matrix** updates dynamically based on user engagement, influencing recommendation scores.

### 🔹 Personalized Recommendation System
- Generates recommendations based on historical user interactions.
- Suggests products that users **haven’t interacted with** but have a **positive recommendation score**.
- Scores are computed from the **weights matrix**, ensuring relevant and personalized product suggestions.

## 📂 File Structure
```
📁 E-commerce-Platform
│-- 📄 main.c  # Core implementation of the platform
```

## ⚙️ How to Run
### 🔹 Prerequisites
Ensure you have a **C compiler** (like GCC) installed on your system.

### 🔹 Compilation Steps
1️⃣ Compile the code:
```sh
gcc main.c -o main.exe
```
2️⃣ Run the executable:
```sh
./main.exe
```

## 🚀 Future Enhancements
- Implementing **collaborative filtering** for better recommendations.
- Optimizing **graph traversal algorithms** for improved efficiency.
- Adding **database integration** to store persistent user data.

---
💡 **Enhance the shopping experience with AI-powered recommendations!** 🛍️
