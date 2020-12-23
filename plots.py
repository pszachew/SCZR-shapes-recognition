import matplotlib.pyplot as plt
import sys
import math
import statistics 

MODE = 'r'
POINTS = 3


def list_stoi(list):
    for i in range(len(list)):
        list[i] = int(list[i])

    return list

def get_data_from_file(file_name):
    message_data = []

    with open(file_name, MODE) as file:
        for line in file.readlines():
            message_data.append(list_stoi(line.strip().split(' ')))

    return message_data


def main():
	argv = sys.argv[1:]
	times = get_data_from_file(argv[0])
	delays = [[],[],[],[]]

	for i in range(len(times)):
			delays[0].append(times[i][0])
			delays[1].append(times[i][1])
			delays[2].append(times[i][2])
			delays[3].append(times[i][3])
			
	names = ['A-B', 'B-C', 'B-D', 'C-D']
	colors = ['red', 'green', 'blue', 'yellow']

	plt.hist(delays, 20, density=False, color=colors,label=names)
	plt.legend(prop={'size': 10})
	# plt.xlim([0,100])
	plt.savefig('build/delay_all.png')
	plt.clf()

	log_file = open('build/stats.log', 'w')
	log_file.write("Delay A-B:\n")
	log_file.write("Arithmetic mean: " + str(round(statistics.mean(delays[0]),POINTS)) + " ms\n")
	log_file.write("Standard Deviation: " + str(round(statistics.stdev(delays[0]),POINTS)) + " ms\n")
	log_file.write("Variance: " + str(round(statistics.variance(delays[0]),POINTS)) + " ms\n")

	log_file.write("Delay B-C:\n")
	log_file.write("Arithmetic mean: " + str(round(statistics.mean(delays[1]),POINTS)) + " ms\n")
	log_file.write("Standard Deviation: " + str(round(statistics.stdev(delays[1]),POINTS)) + " ms\n")
	log_file.write("Variance: " + str(round(statistics.variance(delays[1]),POINTS)) + " ms\n")

	log_file.write("Delay B-D:\n")
	log_file.write("Arithmetic mean: " + str(round(statistics.mean(delays[2]),POINTS)) + " ms\n")
	log_file.write("Standard Deviation: " + str(round(statistics.stdev(delays[2]),POINTS)) + " ms\n")
	log_file.write("Variance: " + str(round(statistics.variance(delays[2]),POINTS)) + " ms\n")

	log_file.write("Delay C-D:\n")
	log_file.write("Arithmetic mean: " + str(round(statistics.mean(delays[3]),POINTS)) + " ms\n")
	log_file.write("Standard Deviation: " + str(round(statistics.stdev(delays[3]),POINTS)) + " ms\n")
	log_file.write("Variance: " + str(round(statistics.variance(delays[3]),POINTS)) + " ms\n")

	log_file.close()

if __name__ == '__main__':
    main()

