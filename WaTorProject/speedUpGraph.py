import matplotlib.pyplot as plt
import numpy as np
import statistics as stats
from scipy.interpolate import make_interp_spline 

one_thread = [63.276478,59.333477,59.922108,61.048109,61.370325,64.003570,60.466899,60.743967,59.773087,59.654452]
one_thread_mean = stats.mean(one_thread)

two_thread = [43.935010,41.033813,40.091455,41.120190,40.567419,40.725110,41.317072,40.647178,40.567044,41.154363]
two_thread_mean = stats.mean(two_thread)

four_thread = [31.697651,32.939508,32.913935,32.055303,31.677157,32.769887,31.765002,31.933011,33.507065,32.612889]
four_thread_mean = stats.mean(four_thread)

eight_thread = [36.392563,36.061277,36.761723,36.780755,36.460433,36.216465,36.853231,36.695638,36.728441,37.002510]
eight_thread_mean = stats.mean(eight_thread)

sixteen_thread = [38.502207,37.564956,38.157320,37.728484,37.407232,37.584547,37.693827,37.518832,37.633723,38.328145]
sixteen_thread_mean = stats.mean(sixteen_thread)

x = np.array([1,2,4,8,16])
y = np.array([one_thread_mean,two_thread_mean,four_thread_mean,eight_thread_mean,sixteen_thread_mean])

y_errormin =[one_thread_mean - min(one_thread), two_thread_mean - min(two_thread), four_thread_mean - min(four_thread), eight_thread_mean - min(eight_thread), sixteen_thread_mean - min(sixteen_thread)]
y_errormax =[max(one_thread) - one_thread_mean, max(two_thread) - two_thread_mean, max(four_thread) - four_thread_mean, max(eight_thread) - eight_thread_mean, max(sixteen_thread) - sixteen_thread_mean]

y_error =[y_errormin, y_errormax]

plt.figure(figsize=(20,20))

font1 = {'family':'serif','color':'blue','size':25}
font2 = {'family':'serif','color':'red','size':20}

plt.title("Speed Up of Wa-Tor Execution Time based on Number of Threads Utilised", fontdict=font1)
plt.xlabel("Number of Threads", fontdict= font2)
plt.ylabel("Time taken to execute (in seconds)", fontdict=font2)

plt.plot(x,y)

plt.yticks(np.arange(29, 66, 1.0))

plt.errorbar(x, y, yerr = y_error, fmt ='o')

plt.show()