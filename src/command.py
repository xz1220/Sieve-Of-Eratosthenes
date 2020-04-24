
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
    return mean


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

    RunTime=np.zeros([4,16])
    for i in range(4):
        for j in range(16):
            RunTime[i][j]= Collect_Runing_Data(j+1,100000000,i+1,20)
    # # print("测试版本1和版本2 之间的性能差异，在number过大的时候，性能提升明显")
    # RunTime[0][0] = Collect_Runing_Data(1,100000000,1)   # average: 5.876134
    # # Collect_Runing_Data(1,100000000,2)   # average: 5.584640
    # # print("\n")
    # # # 61.2% improvement
    


    # RunTime[0][1] = Collect_Runing_Data(2,100000000,1)   # average: 4.203916
    # # Collect_Runing_Data(2,100000000,2)   # average: 4.175527
    # # print("\n")
    # # # 64.4% improvement
    


    # RunTime[0][2] = Collect_Runing_Data(3,100000000,1)   # average: 0.310939
    # # Collect_Runing_Data(4,100000000,2)   # average: 0.309278
    # # print("\n")
    # # 71.5% improvement

    # RunTime[0][3] = Collect_Runing_Data(4,100000000,1)   # average: 0.314161
    # # Collect_Runing_Data(8,100000000,2)   # average: 0.316455
    # # print("\n")
    # # 77.8% improvement

    # RunTime[0][4] = Collect_Runing_Data(5,100000000,1)
    # RunTime[0][5] = Collect_Runing_Data(6,100000000,1)
    # RunTime[0][6] = Collect_Runing_Data(7,100000000,1)
    # RunTime[0][7] = Collect_Runing_Data(8,100000000,1)
    # RunTime[0][8] = Collect_Runing_Data(9,100000000,1)
    # RunTime[0][9] = Collect_Runing_Data(10,100000000,1)
    # RunTime[0][10] = Collect_Runing_Data(11,100000000,1)
    # RunTime[0][11] = Collect_Runing_Data(12,100000000,1)
    # RunTime[0][12] = Collect_Runing_Data(13,100000000,1)
    # RunTime[0][13] = Collect_Runing_Data(14,100000000,1)
    # RunTime[0][14] = Collect_Runing_Data(15,100000000,1)
    # RunTime[0][15] = Collect_Runing_Data(16,100000000,1)


    # # print("测试版本2和版本3 之间的性能差异，在number过大的时候，版本3性能下降")

    # RunTime[1][0] = Collect_Runing_Data(1,100000000,2)   # average: 5.876134
    # # Collect_Runing_Data(1,100000000,3)   # average: 5.584640
    # # print("\n")
    # # # # 61.2% improvement
    


    # RunTime[1][1] = Collect_Runing_Data(2,100000000,2)   # average: 4.203916
    # # Collect_Runing_Data(2,100000000,3)   # average: 4.175527
    # # print("\n")
    # # # # 64.4% improvement
    


    # RunTime[1][2] = Collect_Runing_Data(3,100000000,2)   # average: 0.310939
    # # Collect_Runing_Data(4,100000000,3)   # average: 0.309278
    # # print("\n")
    # # # 71.5% improvement

    # RunTime[1][3] = Collect_Runing_Data(4,100000000,2)   # average: 0.314161
    # # Collect_Runing_Data(8,100000000,3)   # average: 0.316455
    # # print("\n")
    # # # 77.8% improvement
    # RunTime[1][4] = Collect_Runing_Data(5,100000000,2)
    # RunTime[1][5] = Collect_Runing_Data(6,100000000,2)
    # RunTime[1][6] = Collect_Runing_Data(7,100000000,2)
    # RunTime[1][7] = Collect_Runing_Data(8,100000000,2)
    # RunTime[1][8] = Collect_Runing_Data(9,100000000,2)
    # RunTime[1][9] = Collect_Runing_Data(10,100000000,2)
    # RunTime[1][10] = Collect_Runing_Data(11,100000000,2)
    # RunTime[1][11] = Collect_Runing_Data(12,100000000,2)
    # RunTime[1][12] = Collect_Runing_Data(13,100000000,2)
    # RunTime[1][13] = Collect_Runing_Data(14,100000000,2)
    # RunTime[1][14] = Collect_Runing_Data(15,100000000,2)
    # RunTime[1][15] = Collect_Runing_Data(16,100000000,2)

    # # 降低数据量进行测试
    # # Collect_Runing_Data(8,10000000,2)   # average: 0.014566
    # # Collect_Runing_Data(8,10000000,3)   # average: 0.011326
    # # print("\n")
    # # # 77.8% improvement

    # # Collect_Runing_Data(16,50000000,2)   # average: 0.099675
    # # Collect_Runing_Data(16,50000000,3)   # average: 0.067629
    # # print("\n")
    # # # 77.8% improvement

    # # print("测试版本3和版本4 之间的性能差异")

    # RunTime[2][0] = Collect_Runing_Data(1,100000000,3)   # average: 5.709575
    # RunTime[3][0] = Collect_Runing_Data(1,100000000,4)   # average: 2.213405
    # # print("\n")
    # # # # 61.2% improvement
    


    # RunTime[2][1] = Collect_Runing_Data(2,100000000,3)   # average: 4.183135
    # RunTime[3][1] = Collect_Runing_Data(2,100000000,4)   # average: 1.488893
    # # print("\n")
    # # # # 64.4% improvement
    


    # RunTime[2][2] = Collect_Runing_Data(3,100000000,3)   # average: 0.329979
    # RunTime[3][2] = Collect_Runing_Data(3,100000000,4)   # average: 0.094075
    # # print("\n")
    # # # 71.5% improvement

    # RunTime[2][3] = Collect_Runing_Data(4,100000000,3)   # average: 0.317144
    # RunTime[3][3] = Collect_Runing_Data(5,100000000,4)   # average: 0.070440
    # # print("\n")
    # # # 77.8% improvement

    # RunTime[2][4] = Collect_Runing_Data(5,100000000,3)
    # RunTime[2][5] = Collect_Runing_Data(6,100000000,3)
    # RunTime[2][6] = Collect_Runing_Data(7,100000000,3)
    # RunTime[2][7] = Collect_Runing_Data(8,100000000,3)
    # RunTime[2][8] = Collect_Runing_Data(9,100000000,3)
    # RunTime[2][9] = Collect_Runing_Data(10,100000000,3)
    # RunTime[2][10] = Collect_Runing_Data(11,100000000,3)
    # RunTime[2][11] = Collect_Runing_Data(12,100000000,3)
    # RunTime[2][12] = Collect_Runing_Data(13,100000000,3)
    # RunTime[2][13] = Collect_Runing_Data(14,100000000,3)
    # RunTime[2][14] = Collect_Runing_Data(15,100000000,3)
    # RunTime[2][15] = Collect_Runing_Data(16,100000000,3)

    # RunTime[3][4] = Collect_Runing_Data(5,100000000,4)
    # RunTime[3][5] = Collect_Runing_Data(6,100000000,4)
    # RunTime[3][6] = Collect_Runing_Data(7,100000000,4)
    # RunTime[3][7] = Collect_Runing_Data(8,100000000,4)
    # RunTime[3][8] = Collect_Runing_Data(9,100000000,4)
    # RunTime[3][9] = Collect_Runing_Data(10,100000000,4)
    # RunTime[3][10] = Collect_Runing_Data(11,100000000,4)
    # RunTime[3][11] = Collect_Runing_Data(12,100000000,4)
    # RunTime[3][12] = Collect_Runing_Data(13,100000000,4)
    # RunTime[3][13] = Collect_Runing_Data(14,100000000,4)
    # RunTime[3][14] = Collect_Runing_Data(15,100000000,4)
    # RunTime[3][15] = Collect_Runing_Data(16,100000000,4)



    np.save("./Data/RunTime.npy",RunTime)

def Version_2_3():
    RunTime=np.zeros([5,21])

    for i in range(5):
        for j in range(21):
            n=1000000000/(10**(i+1))
            data1 = Collect_Runing_Data(j+1,n,2,2**(i+1)) 
            data2 = Collect_Runing_Data(j+1,n,3,2**(i+1))
            RunTime[i][j] =(data1-data2)/data1

    np.save("./Data/Version_2_3.npy",RunTime)


if __name__ == "__main__":
    main()