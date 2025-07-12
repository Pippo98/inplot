import sys
sys.path.append('./../../lib/')
from pyinplot import *

import numpy as np

f = Figure(" ")

xx = np.linspace(1, 100, 10000, dtype="float64")
yy = np.sin(xx)

f.AddPlot("plot 1")
id = f.AddLinePlot("line1", xx, yy)

f.AddPlot("plot 2")
id = f.AddLinePlot("line2", xx, yy)

f.AddPlot3("plot 2")
id = f.AddLinePlot3("line2", xx, yy, xx)
id = f.AddScatterPlot3("line2", xx, yy, xx)

f.WaitForEnd();

