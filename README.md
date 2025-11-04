# 🧩 Philosophers

![42 Project](https://img.shields.io/badge/42%20Project-Philosophers-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen?style=for-the-badge)

---

## 🧠 Overview

**Philosophers** is a classic concurrency project that simulates the **Dining Philosophers Problem** using **threads and mutexes** in C.  

The goal is to manage multiple philosophers who **think, eat, and sleep** while sharing limited resources (forks) without causing **deadlocks** or starvation.  

This project reinforces **multithreading, synchronization, and time management** in concurrent programming.

---

## 🧩 Key Objectives

- Implement **threaded philosophers** using `pthread`  
- Prevent **deadlocks** and ensure all philosophers eat  
- Track time accurately to detect **starvation and death**  
- Use **mutexes** to control access to shared forks  
- Follow **Norminette** rules strictly  

---

## ⚙️ Installation & Usage

Clone the repository:
```bash
git clone https://github.com/TheGoldenDua/philosophers.git
cd philosophers
