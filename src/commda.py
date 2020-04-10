
import os
import numpy as np

def Collect_Runing_Data(processes, number, version=1,runtime=5):
    # 判断参数是否合法
    assert processes>=1
    assert number>=100

    time_collection=[]

    
    # 收集参数
    for i in range(runtime):
        result=os.popen('mpiexec -n %d .\sieve%d.exe %d'%(processes,version,number)).read()
        # print(result)
        time=float(result[len(result)-10:])
        # print(time)
        time_collection.append(time)
    
    
    time_array=np.array(time_collection)
    mean=time_array.mean()

    print("版本:%d,进程数：%d,范围在%d以内，运行次数:%d,平均运行时间：%f"%(version,processes,number,runtime,mean))


def main():
    # processes=input("请输入进程数：")
    # try:
    #     processes=int(processes)
    # except:
    #     print("进程数输入错误")
    #     raise

    # number=input("请输入n：")
    # try:
    #     number=int(number)
    # except:
    #     print("Number is error!")
    #     raise

    # print("测试版本1和版本2 之间的性能差异，在number过大的时候，性能提升明显")
    # Collect_Runing_Data(1,1000,1)
    # Collect_Runing_Data(1,1000,2)
    # 
    # Collect_Runing_Data(1,100000,1)
    # Collect_Runing_Data(1,100000,2)
    # 
    # Collect_Runing_Data(4,1000,1)
    # Collect_Runing_Data(4,1000,2)
    # 
    # Collect_Runing_Data(4,1000000,1)
    # Collect_Runing_Data(4,1000000,2)
    # 

    # print("测试版本2和版本3 之间的性能差异，在number过大的时候，版本3性能下降")

    # Collect_Runing_Data(1,1000,2)
    # Collect_Runing_Data(1,1000,3)
    
    # Collect_Runing_Data(2,1000,2)
    # Collect_Runing_Data(2,1000,3)
    
    # Collect_Runing_Data(2,10000,2)
    # Collect_Runing_Data(2,10000,3)
    
    # Collect_Runing_Data(4,10000,2)
    # Collect_Runing_Data(4,10000,3)
    
    # Collect_Runing_Data(4,20000,2)
    # Collect_Runing_Data(4,20000,3)
    

    # print("测试版本3和版本4 之间的性能差异")

    # Collect_Runing_Data(1,1000000000,3)   # average: 11.37
    # Collect_Runing_Data(1,1000000000,4)   # average: 6.81
    # # 40% improvement
    # 


    # Collect_Runing_Data(2,1000000000,3)   # average: 7.16
    # Collect_Runing_Data(2,1000000000,4)   # average: 4.79
    # # 33% improvement
    # 


    # Collect_Runing_Data(3,100000000,3)   # average: 0.565
    # Collect_Runing_Data(3,100000000,4)   # average: 0.349
    # 38%% improvement
    


if __name__ == "__main__":
    main()    
    