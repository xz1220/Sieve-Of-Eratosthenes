;;配置clang 的导入目录
(
 (nil . (
         (company-clang-arguments . ("-I/usr/lib64/mpi/gcc/openmpi/include/"
                                     "-I/home/xingzheng/mpi-exp/perf/"
                                     "-I/usr/include/"
                                     "-I/usr/local/include/"))
         ;;(add-to-list 'company-c-headers-path-system "/usr/include")
         ))
 )

(add-to-list 'company-c-headers-path-system "/usr/include/")
(add-to-list 'company-c-headers-path-system "/usr/local/include/")
(add-to-list 'company-c-headers-path-system "/usr/lib64/mpi/gcc/openmpi/include/")
(add-to-list 'company-c-headers-path-user "/home/xingzheng/mpi-exp/perf/")
