import numpy as np
import matplotlib.pyplot as plt

profundidad=2.0
c=1.0

x_inicial=0.0
x_final=30.0
n_x=302
dx=(x_final-x_inicial)/300

y_inicial=0.0
y_final=30.0
n_y=302
dy=(y_inicial-y_final)/n_y

t_inicial=0.0
t_final=60.0
n_t=1000
dt=(t_final-t_inicial)/1000

t_inicial=0.0
t_final=60.0
n_t=1000
t=np.linspace(t_inicial, t_final)
dt=(t_final-t_inicial)/1000

u_inicial=np.zeros((n_x, n_y))
u_inicial[n_x/2][n_x/3]=-0.5

r=(c*dt)/dx

u_pasado=np.zeros((n_t, n_x, n_y))
u_pasado[0] = 0.0;
u_pasado[n_x-1] = 0.0;

u_presente=np.zeros((n_t, n_x, n_y))
u_presente[0] = 0.0;
u_presente[n_x-1] = 0.0;

u_futuro=np.zeros((n_t, n_x, n_y))

#Primera iteracion 2 for y
for i in range(1, n_x-1): 
		u_presente[i] = u_inicial[i] + ((r**2.0)/2.0) * (u_inicial[i+1] - 2.0 * u_inicial[i] + u_inicial[i-1])


#Iteraciones 3 for t, x, y 
for i in range(1, n_x-1):
    u_futuro[i] = (2.0 * (1.0 - ((r**2.0)/2.0)))*u_presente[i] - u_pasado[i] + (((r**2.0)/2.0))*(u_presente[i+1] + u_presente[i-1])
    u_pasado=u_presente.copy()
    u_presente=u_futuro.copy()
