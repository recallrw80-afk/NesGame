# NES 模拟器（C++）项目记忆

## 项目状态

### 已完成组件

| 文件                      | 状态    | 说明                                                                                                       |
| ------------------------- | ------- | ---------------------------------------------------------------------------------------------------------- |
| `include/basic/types.h`   | ✅ 完成 | u8/u16/u32/u64/i8/i16/i32/i64/f32/f64 类型别名                                                             |
| `include/nes/Mapper.h`    | ✅ 完成 | Mapper 抽象基类 (cpu_map_read/write, ppu_map_read/write)                                                   |
| `include/nes/Mapper0.h`   | ✅ 完成 | Mapper0 (NROM) 实现，无 bank switching                                                                     |
| `include/nes/Cartridge.h` | ✅ 完成 | Cartridge 声明：PRG/CHR ROM、SRAM、Mapper、iNES 头部字段                                                   |
| `src/Cartridge.cpp`       | ✅ 完成 | iNES 文件加载、头部解析、Mapper 创建、CPU/PPU 读写转发                                                     |
| `include/nes/Bus.h`       | ✅ 完成 | Bus 声明：cpu_ram (2KB)、Cartridge 指针、CPU 指针                                                          |
| `src/Bus.cpp`             | ✅ 完成 | 64KB 地址空间解码，CPU RAM 读写，PPU/APU/Cartridge 地址路由                                                |
| `include/nes/PPU.h`       | ✅ 完成 | PPU 声明：VRAM (2KB)、调色板 (32B)、8 个寄存器、写锁存、读缓冲                                             |
| `src/PPU.cpp`             | ✅ 完成 | PPU 寄存器读写完整逻辑（PPUCTRL/PPUMASK/PPUSTATUS/PPUSCROLL/PPUADDR/PPUDATA），VRAM/调色板镜像，读缓冲延迟 |
| `include/nes/CPU.h`       | 🚧 进行中 | 寄存器/标志位/寻址模式/指令函数声明、Instruction 结构体与 256 项操作码表声明（已补 TYA 声明）             |
| `src/CPU.cpp`             | 🚧 进行中 | 256 项操作码表（已验证：151 条官方指令全部正确，其余 XXX）、辅助函数、寻址模式 6/13（IMP/IMM/ZP0/ZPX/ZPY/ABX）；指令函数体未实现，链接失败属正常 |
| `src/Mapper.cpp`          | 📄 空   | 占位                                                                                                       |
| `src/DMA.cpp`             | 📄 空   | 占位                                                                                                       |
| `src/APU.cpp`             | 📄 空   | 占位                                                                                                       |
| `main.cpp`                | ✅ 完成 | 加载 ROM、打印 Cartridge 信息（DEBUG 模式）                                                                |
| `CMakeLists.txt`          | ✅ 完成 | C++20、GLOB_RECURSE 收集 src/*.cpp、多编译器警告选项                                                       |

### 已知问题

1. **Bus.cpp:53-58 地址解码 bug** — PPU 和 APU 的 `if` 分支都检查了 `PPU_REG_BASE..PPU_REG_END`，第二个应检查 `APU_IO_BASE..APU_IO_END`。当前 APU 寄存器读写被错误跳过。
2. **PPU.cpp:14-21 寄存器偏移常量命名错位** — 偏移 3 命名为 `PPUADDR`（实为 OAMADDR $2003），偏移 5 命名为 `OAMADDR`（实为 PPUSCROLL $2005），偏移 6 命名为 `PPUSCROLL`（实为 PPUADDR $2006）。register_read 的 switch-case 用 `PPUADDR` case 处理了实际 PPUDATA 的逻辑（$2007），也存在逻辑问题。
3. **Bus 未连接 PPU** — `Bus` 没有 PPU 指针成员，`cpu_read`/`cpu_write` 中 PPU 寄存器访问直接 `return 0`（标记 TODO）。

### 下一步

1. **用户在写剩余寻址模式（教学模式）** — 已示范 ABS 和 IZX 两个示例；留给用户自己写：ABY（照抄 ABX 换 y）、ACC、REL（i8 有符号偏移存 addr_rel）、IZY（先读零页指针再加 y、处理跨页加周期）、IND（仅 JMP 用，复现 $xxFF 硬件 bug）。写完帮 review 并一起编译
2. 实现全部指令函数体和 reset/step/nmi/irq
3. 修复 Bus.cpp 地址解码 bug
4. 修复 PPU.cpp 寄存器偏移常量命名
5. Bus 连接 PPU
6. 实现 APU 和 DMA

## 教学模式约定 ⭐

- **用户在学习 6502/NES 原理，要求"示范 + 自己动手"的工作方式**：给示例代码并讲清原理，留同类练习让用户自己写，不要直接全部实现
- 已讲过的概念：mode()/oper() 分离设计（寻址模式函数只负责算 addr_abs 并推进 pc）、小端序、零页回绕、间接寻址（IZX 三步取址）、跨页加周期

## 架构约定

- 每次文件更改都要执行 `codegraph sync`（在 cpp/ 目录下运行）
- 类型：u8/u16/u32/u64（定义在 basic/types.h）
- C++20 标准，禁用编译器扩展（`CMAKE_CXX_EXTENSIONS OFF`）
- 命名：成员变量 snake_case，类 PascalCase
- 构造函数使用初始化列表（参考 Bus 风格）
- Bus 是中央枢纽，连接 CPU、PPU、Cartridge
- 构建：`cd cpp/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .`
