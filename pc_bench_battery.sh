#!/bin/bash

# Symmetric, high latency, no backoff, 10 iterations, 5 million productions per producer
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 1 1 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 2 2 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 4 4 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 8 8 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 16 16 5000000 1 2000 2000

perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 1 1 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 2 2 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 4 4 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 8 8 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 16 16 5000000 1 2000 2000

perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 1 1 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 2 2 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 4 4 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 8 8 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 16 16 5000000 1 2000 2000

perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 1 1 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 2 2 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 4 4 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 8 8 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 16 16 5000000 1 2000 2000

# Asymmetric (1p2c), high latency, no backoff, 10 iterations, 5 million productions per producer
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 1 2 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 2 4 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 4 8 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 8 16 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 16 32 5000000 1 2000 2000

perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 1 2 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 2 4 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 4 8 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 8 16 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 16 32 5000000 1 2000 2000

perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 1 2 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 2 4 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 4 8 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 8 16 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 16 32 5000000 1 2000 2000

perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 1 2 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 2 4 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 4 8 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 8 16 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 16 32 5000000 1 2000 2000

# Asymmetric (2p1c), high latency, no backoff, 10 iterations, 5 million productions per producer
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 2 1 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 4 2 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 8 4 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 16 8 5000000 1 2000 2000
perf stat -o pc_bench_lf_stack_high_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 32 16 5000000 1 2000 2000

perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 2 1 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 4 2 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 8 4 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 16 8 5000000 1 2000 2000
perf stat -o pc_bench_lb_stack_high_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 32 16 5000000 1 2000 2000

perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 2 1 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 4 2 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 8 4 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 16 8 5000000 1 2000 2000
perf stat -o pc_bench_lf_queue_high_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 32 16 5000000 1 2000 2000

perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 2 1 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 4 2 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 8 4 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 16 8 5000000 1 2000 2000
perf stat -o pc_bench_lb_queue_high_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 32 16 5000000 1 2000 2000

# Symmetric, low latency, no backoff, 10 iterations, 5 million productions per producer
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 1 1 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 2 2 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 4 4 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 8 8 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 16 16 5000000 1 100 100

perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 1 1 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 2 2 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 4 4 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 8 8 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 16 16 5000000 1 100 100

perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 1 1 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 2 2 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 4 4 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 8 8 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 16 16 5000000 1 100 100

perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_symmetric_2.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 1 1 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_symmetric_4.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 2 2 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_symmetric_8.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 4 4 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_symmetric_16.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 8 8 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_symmetric_32.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 16 16 5000000 1 100 100

# Asymmetric (1p2c), low latency, no backoff, 10 iterations, 5 million productions per producer
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 1 2 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 2 4 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 4 8 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 8 16 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 16 32 5000000 1 100 100

perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 1 2 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 2 4 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 4 8 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 8 16 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 16 32 5000000 1 100 100

perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 1 2 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 2 4 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 4 8 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 8 16 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 16 32 5000000 1 100 100

perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_1p2c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 1 2 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_1p2c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 2 4 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_1p2c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 4 8 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_1p2c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 8 16 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_1p2c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 16 32 5000000 1 100 100

# Asymmetric (2p1c), low latency, no backoff, 10 iterations, 5 million productions per producer
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 2 1 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 4 2 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 8 4 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 16 8 5000000 1 100 100
perf stat -o pc_bench_lf_stack_low_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf stack none 32 16 5000000 1 100 100

perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 2 1 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 4 2 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 8 4 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 16 8 5000000 1 100 100
perf stat -o pc_bench_lb_stack_low_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb stack none 32 16 5000000 1 100 100

perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 2 1 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 4 2 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 8 4 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 16 8 5000000 1 100 100
perf stat -o pc_bench_lf_queue_low_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lf queue none 32 16 5000000 1 100 100

perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_2p1c_3.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 2 1 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_2p1c_6.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 4 2 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_2p1c_12.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 8 4 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_2p1c_24.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 16 8 5000000 1 100 100
perf stat -o pc_bench_lb_queue_low_no_bs_10it_5m_asymmetric_2p1c_48.log -r 10 -e task-clock,cache-references,cache-misses,LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses bin/pc-bench lb queue none 32 16 5000000 1 100 100

