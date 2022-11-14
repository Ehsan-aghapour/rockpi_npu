import numpy as np
def show_outputs(outputs):
	output = outputs[0][0]
	output_sorted = sorted(output, reverse=True)
	top5_str = 'mobilenet_v1\n-----TOP 5-----\n'
	for i in range(5):
		value = output_sorted[i]
		index = np.where(output == value)
		for j in range(len(index)):
			if (i + j) >= 5:
				break
			if value > 0:
				topi = '{}: {}\n'.format(index[j], value)
			else:
				topi = '-1: 0.0\n'
			top5_str += topi
	print(top5_str)
