# 1 module port PCC
## 1.2 Over view PCC 
-  Peripheral colock control (PCC) module cung cấp xung clock và các cấu hình cho các ngoại vi trên chip.
## 1.3 PCC feature 
- PCC module cho phép software cấu hình các lựa chọn clock bên dưới cho các ngoại vi
->interface clocking gating 
-> Functional clock source selection 
-> Functional clock divide values 
![alt text](image.png)

## 1.4 PCC Functional

* PCC (Peripheral Clock Control): mỗi ngoại vi (module) có một thanh ghi PCC riêng để điều khiển cấp clock và cấu hình.

* Mỗi thanh ghi PCC có bit CGC (Clock Gating Control) để bật/tắt clock cho module.

  * Muốn sử dụng module → phải bật clock (CGC = 1).

  * Trước khi cấu hình clock cho module → phải tắt clock (CGC = 0).

* Ngoài ra, PCC có các trường cấu hình:

  * PCS (Peripheral Clock Select): chọn nguồn clock.

  * PCD (Peripheral Clock Divider) và FRAC (Fraction): chia tần số clock.

ví dụ: config pcc cho port D 

```c 
#define PCC_BASE        (0x40065000u)
#define PCC_PORTD       (*(volatile uint32_t *)(PCC_BASE + 0x130))
#define PCC_CGC         (1u << 30)  // ghi 1 ở chân 30 để enable cho port D 
 ``` 
 ---
### 1.2. Tìm hiểu về module PCC
- **PCC (Peripheral Clock Control)** là module quản lý và cung cấp xung clock cho các peripheral trong vi điều khiển S32K.
- Mỗi peripheral (PORT, GPIO, LPUART, SPI, v.v.) đều có bit điều khiển clock trong thanh ghi PCC.
- Muốn sử dụng một peripheral thì trước tiên phải **enable clock** cho nó trong thanh ghi PCC tương ứng.
- Ví dụ: để bật clock cho **PORTD**, ta ghi `1` vào bit `CGC` (bit 30) của thanh ghi `PCC_PORTD`.

---

### 1.3. Tìm hiểu về module PORT và tiến hành configure PORT cho PTD0, PTD15, PTD16
- **PORT** (Pin Control and Interrupts) là module quản lý chức năng (multiplexing) của từng chân pin.
- Mỗi chân pin có một thanh ghi `PORTx_PCRn` để chọn chức năng pin (GPIO, UART, SPI, v.v.) thông qua trường `MUX`.
- Muốn dùng chân pin làm GPIO thì cần cấu hình `MUX = 1`.
- Cụ thể:
```c
  PORTD_PCR0 = (1 << 8)` → cấu hình PTD0 là GPIO.
  PORTD_PCR15 = (1 << 8)` → cấu hình PTD15 là GPIO.
  PORTD_PCR16 = (1 << 8)` → cấu hình PTD16 là GPIO.
```
---

### 1.4. Tìm hiểu về module GPIO và tiến hành configure cho PTD0, PTD15, PTD16
- **GPIO (General-Purpose Input/Output)** là module cho phép pin hoạt động như ngõ ra hoặc ngõ vào số.
- Mỗi port có các thanh ghi:
  - `PDDR` : chọn hướng dữ liệu (0 = input, 1 = output).
  - `PSOR` : set bit output lên mức logic 1.
  - `PCOR` : clear bit output xuống mức logic 0.
  - `PTOR` : toggle giá trị output.
  - `PDIR` : đọc dữ liệu input từ chân.
- Với PTD0, PTD15, PTD16 muốn làm output thì set bit tương ứng trong thanh ghi `GPIOD_PDDR`.
  ```c
  GPIOD->PDDR |= (1 << 0) | (1 << 15) | (1 << 16);
  ```

[File bài tập Blink led](https://drive.google.com/drive/folders/1DAXoBPCt3Dv4uWydv8faL6jjqxgtz2rM)