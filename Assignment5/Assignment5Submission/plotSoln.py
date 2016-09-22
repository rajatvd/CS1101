from matplotlib.pyplot import *
def plotData(filename):
    """Plots the data in the file with relative path filename assuming the columns are time, x and v respectively."""
    fo = open(filename, 'r')
    lines = fo.read().split("\n")
    fo.close()
    t = []
    x = []
    v = []
    # Extract values:
    for i in lines[:-1]:
        values = i.split("\t")
    
        t.append(float(values[0]))
        x.append(float(values[1]))
        v.append(float(values[2]))
    
    # Plot data:
    # Figure 1 - time domain
    xlabel("Time (sec)")
    ylabel("States")
    title("Time evolution of Mass-Spring system")
    plot(t,x)
    plot(t,v)
    legend(('$x$ (m)', '$v$ (m/sec)'))
    
    # Figure 2 - phase space
    figure()
    plot(x,v)
    title("Phase space")
    xlabel("$x$ (m)")
    ylabel("$v$ (m/sec)")
    show()    
    
    
def plotData2(filename):
    """Plots the data in the file with relative path filename assuming the columns are time, x and y respectively."""
    fo = open(filename, 'r')
    lines = fo.read().split("\n")
    fo.close()
    t = []
    x = []
    y = []
    # Extract values:
    for i in lines[:-1]:
        values = i.split("\t")
    
        t.append(float(values[0]))
        x.append(float(values[1]))
        y.append(float(values[2]))
    
    # Plot data:
    # Figure 1 - time domain
    xlabel("Time")
    ylabel("Population")
    title("Time evolution of Predator-Prey system")
    plot(t,x)
    plot(t,y)
    legend(('$x$ (prey)', '$y$ (predator)'))
    
    # Figure 2 - phase space
    figure()
    plot(x,y)
    title("Phase space")
    xlabel("$x$ (prey population)")
    ylabel("$y$ (predator population)")
    show()

plotData2("solution.txt")
