import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

path = 'results\\'


# Domain = 30, TMAX = 10000, sims: 200
def show_yes_fraction_2d():
    data0 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_0.dat')
    data03 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_03.dat')
    data05 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_05.dat')
    data07 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_07.dat')
    data10 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_10.dat')
    data15 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_15.dat')
    data20 = np.loadtxt(path + 'yes_fraction\\sm2d_yes_20.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.title('Fraction of agents with all spins up vs. initial density of up spins ($C_u$)',
              fontsize=10)
    plt.plot(data0[:, 0], data0[:, 1], '-o')
    plt.plot(data03[:, 0], data03[:, 1], '-v')
    plt.plot(data05[:, 0], data05[:, 1], '-^')
    plt.plot(data07[:, 0], data07[:, 1], '-<')
    plt.plot(data10[:, 0], data10[:, 1], '->')
    plt.plot(data15[:, 0], data15[:, 1], '-s')
    plt.plot(data20[:, 0], data20[:, 1], '-d')

    # plt.ylim(0)
    plt.xlim(0.02)

    plt.legend(['p=0.0', 'p=0.03', 'p=0.05', 'p=0.07', 'p=0.10', 'p=0.15', 'p=0.20'])
    plt.ylabel('fraction of agents with all spins up')
    plt.xlabel('initial density of up spins ($C_u$)')
    plt.show()


# Domain = 30, TMAX = 10000, sims: 200
def show_yes_fraction_extended_2d():
    data01 = np.loadtxt(path + 'yes_fraction_extended\\sm2d_yes_01.dat')
    data02 = np.loadtxt(path + 'yes_fraction_extended\\sm2d_yes_02.dat')
    data04 = np.loadtxt(path + 'yes_fraction_extended\\sm2d_yes_04.dat')
    data06 = np.loadtxt(path + 'yes_fraction_extended\\sm2d_yes_06.dat')
    data10 = np.loadtxt(path + 'yes_fraction_extended\\sm2d_yes_10.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.title('Fraction of agents with all spins up ($\mathbf{f}$) vs. initial density of up spins ($C_u$)',
              fontsize=10)

    plt.plot(data01[:, 0], data01[:, 1], '-v')
    plt.plot(data02[:, 0], data02[:, 1], '-^')
    plt.plot(data04[:, 0], data04[:, 1], '-<')
    plt.plot(data06[:, 0], data06[:, 1], '->')
    plt.plot(data10[:, 0], data10[:, 1], '-s')

    # plt.ylim(0)
    plt.xlim(0.02)

    plt.legend(['p=0.0', 'p=0.03', 'p=0.05', 'p=0.07', 'p=0.10', 'p=0.15', 'p=0.20'])
    plt.ylabel('fraction of agents with all spins up ($\mathbf{f}$)')
    plt.xlabel('initial density of up spins ($C_u$)')
    plt.show()


# Domain: 100, TMAX: 10000, sims: 200
def show_steady_state_2d():
    data = np.loadtxt(path + 'sm2d_steady.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.plot(data[:, 0], data[:, 1], '^--')
    plt.plot(data[:, 0], data[:, 2], 'v--')

    plt.title('distribution of steady state vs. initial density of up spins')
    plt.legend(['consensus yes (spins up)', 'consensus no (spins down)'])
    plt.ylabel('probability of steady state (magnetization)')
    plt.xlabel('initial density of up spins $C_u$')
    plt.show()


# Domain: 35, TMAX: 10000, sims: 500
def show_relaxation_time_2d1():
    data = np.loadtxt(path + 'sm2d_relaxation.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.plot(data[:, 0], data[:, 1], '--')
    plt.plot(data[:, 0], data[:, 1], 'ro')
    # plt.ylim(-5)
    plt.xlim(0, 1)
    plt.title('relaxation time versus initial density of up spins')
    plt.legend(['relaxation time $\\tau$'])
    plt.ylabel('relaxation time $\\tau$')
    plt.xlabel('initial density of up spins')
    plt.show()


def show_relaxation_time_2d():
    data20 = np.loadtxt(path + 'relaxation_time_domain\\sm2d_relaxation_20.dat')
    data30 = np.loadtxt(path + 'relaxation_time_domain\\sm2d_relaxation_30.dat')
    data40 = np.loadtxt(path + 'relaxation_time_domain\\sm2d_relaxation_40.dat')
    data50 = np.loadtxt(path + 'relaxation_time_domain\\sm2d_relaxation_50.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.plot(data20[:, 0], data20[:, 1], 'o--')
    plt.plot(data30[:, 0], data30[:, 1], 'o--')
    plt.plot(data40[:, 0], data40[:, 1], 'o--')
    plt.plot(data50[:, 0], data50[:, 1], 'o--')

    plt.title('relaxation time versus initial density of up spins')
    plt.legend(['Domain size=20', 'Domain size=30', 'Domain size=40', 'Domain size=60'])
    plt.ylabel('relaxation time $\\tau$')
    plt.xlabel('initial density of up spins $C_u$')

    # plt.ylim(1e-6, .7)
    # plt.xlim(3, 1000)
    plt.show()


# Domain: 100, TMAX: 10000, sims: 1000
def show_steady_state_1d():
    data = np.loadtxt(path + 'sm1d_steady_state.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.plot(data[:, 0], data[:, 1], '^--')
    plt.plot(data[:, 0], data[:, 2], 'v--')
    plt.plot(data[:, 0], data[:, 3], 'o--')

    plt.title('distribution of steady state')
    plt.legend(['consensus yes (spins up)', 'consensus no (spins down)', 'stalemate'])
    plt.ylabel('probability of steady state (magnetization)')
    plt.xlabel('initial density of up spins $C_u$')
    plt.xlim(0)
    plt.ylim(-0.02)
    plt.show()


# Domain = 100, TMAX = 5000, sims: 1000
def show_steady_state_modified_1d():
    data = np.loadtxt(path + 'sm1d_steady_state_modified.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.plot(data[:, 0], data[:, 1], '^--')
    plt.plot(data[:, 0], data[:, 2], 'v--')
    plt.plot(data[:, 0], data[:, 3], 'o--')

    plt.title('distribution of steady state (modified SM model)')
    plt.legend(['consensus yes (spins up)', 'consensus no (spins down)', 'stalemate'])
    plt.ylabel('probability of steady state (magnetization)')
    plt.xlabel('initial density of up spins $C_u$')
    plt.xlim(0)
    plt.ylim(-0.02)
    plt.show()


# Domain: 30, sims: 1000
def show_decision_time_1d():
    data = np.loadtxt(path + 'sm1d_decision_time.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    sum = np.sum(data[:, 1])
    plt.loglog(data[:, 0], data[:, 1] / sum, '+')
    plt.loglog(np.arange(1, 2000, 1), np.arange(1, 2000, 1) ** (-1.6) / 2)

    plt.title('distribution of decision time $\mu$')
    plt.legend(['simulation', 'powerfit ~ $\mu^{-1.5}$'], loc=3)
    plt.ylabel('$P(\mu)$')
    plt.xlabel('decision time $\mu$')
    plt.ylim(1e-5, 1)
    plt.xlim(1, 2000)
    plt.show()


# Domain: 60, sims: 1000
def show_decision_time_2d():
    data = np.loadtxt(path + 'sm2d_decision_time.dat')
    data = np.loadtxt(path + 'decision_time_vs_domain\\sm2d_decision_time_60.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    sum = np.sum(data[:, 1])
    plt.loglog(data[:, 0], data[:, 1] / sum, ':')
    plt.loglog(np.arange(1, 2000, 1), np.arange(1, 2000, 1) ** (-1.8) / 2.2, '--')

    plt.title('distribution of decision time $\mu$, domain size: 60')
    plt.legend(['simulation', 'powerfit ~ $\mu^{-1.8}$'])
    plt.ylabel('$P(\mu)$')
    plt.xlabel('decision time $\mu$')

    plt.ylim(1e-6, .7)
    plt.xlim(3, 1000)
    plt.show()


# sims: 1000
def show_decision_time_vs_domain_2d():
    data20 = np.loadtxt(path + 'decision_time_vs_domain\\sm2d_decision_time_20.dat')
    data30 = np.loadtxt(path + 'decision_time_vs_domain\\sm2d_decision_time_30.dat')
    data40 = np.loadtxt(path + 'decision_time_vs_domain\\sm2d_decision_time_40.dat')
    data60 = np.loadtxt(path + 'decision_time_vs_domain\\sm2d_decision_time_60.dat')
    data80 = np.loadtxt(path + 'decision_time_vs_domain\\sm2d_decision_time_80.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.loglog(data20[:, 0], data20[:, 1] / np.sum(data20[:, 1]), ':')
    plt.loglog(data30[:, 0], data30[:, 1] / np.sum(data30[:, 1]), ':')
    plt.loglog(data40[:, 0], data40[:, 1] / np.sum(data40[:, 1]), ':')
    plt.loglog(data60[:, 0], data60[:, 1] / np.sum(data60[:, 1]), ':')
    plt.loglog(data80[:, 0], data80[:, 1] / np.sum(data80[:, 1]), ':')

    plt.title('distribution of decision time $\mu$')
    plt.legend(['Domain size=20', 'Domain size=30', 'Domain size=40', 'Domain size=60', 'Domain size=80'])
    plt.ylabel('$P(\mu)$')
    plt.xlabel('decision time $\mu$')

    plt.ylim(1e-6, .7)
    plt.xlim(3, 1000)
    plt.show()


# sims: 500, L=60
def show_decision_change_2d():
    data00 = np.loadtxt(path + 'decision_change\\sm2d_decision_change_00.dat')
    data03 = np.loadtxt(path + 'decision_change\\sm2d_decision_change_03.dat')
    data05 = np.loadtxt(path + 'decision_change\\sm2d_decision_change_05.dat')
    data07 = np.loadtxt(path + 'decision_change\\sm2d_decision_change_07.dat')
    data10 = np.loadtxt(path + 'decision_change\\sm2d_decision_change_10.dat')
    data20 = np.loadtxt(path + 'decision_change\\sm2d_decision_change_20.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.loglog(data00[:, 0], data00[:, 1], '-')
    plt.loglog(data03[:, 0], data03[:, 1], 'v--')
    plt.loglog(data05[:, 0], data05[:, 1], '^--')
    plt.loglog(data07[:, 0], data07[:, 1], '<--')
    plt.loglog(data10[:, 0], data10[:, 1], '>--')
    plt.loglog(data20[:, 0], data20[:, 1], 's--')

    plt.title('Number of agents with unchanged state versus time')
    plt.legend(['p=0.0', 'p=0.03', 'p=0.05', 'p=0.07', 'p=0.10', 'p=0.20'])
    plt.ylabel('number of agents with unchanged state')
    plt.xlabel('simulation time $T$')

    plt.xlim(0, 100)
    plt.ylim(10)
    plt.show()


# sims: 500
def show_decision_change_vs_domain_2d():
    data20 = np.loadtxt(path + 'decision_change_vs_domain\\sm2d_decision_change_20.dat')
    data30 = np.loadtxt(path + 'decision_change_vs_domain\\sm2d_decision_change_30.dat')
    data40 = np.loadtxt(path + 'decision_change_vs_domain\\sm2d_decision_change_40.dat')
    data60 = np.loadtxt(path + 'decision_change_vs_domain\\sm2d_decision_change_60.dat')
    data100 = np.loadtxt(path + 'decision_change_vs_domain\\sm2d_decision_change_100.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.loglog(data20[:, 0], data20[:, 1])
    plt.loglog(data30[:, 0], data30[:, 1])
    plt.loglog(data40[:, 0], data40[:, 1])
    plt.loglog(data60[:, 0], data60[:, 1])
    plt.loglog(data100[:, 0], data100[:, 1])
    plt.plot(data100[:, 0], 10 ** (-.28 * np.log10(data100[:, 0]) + 3.45), '--', color='gray', alpha=.7)

    plt.title('Number of agents with unchanged state versus time')
    plt.legend(
        ['Domain size=20', 'Domain size=30', 'Domain size=40', 'Domain size=60', 'Domain size=100', '$t^{-0.28}$'])
    plt.ylabel('number of agents with unchanged state')
    plt.xlabel('simulation time $t$')

    plt.xlim(0, 10000)
    plt.ylim(10)
    plt.show()


# domain: 20-140, sims: 1000
def show_domain_relaxation():
    data = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation.dat')
    data_03 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_03.dat')
    data_05 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_05.dat')
    data_07 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_07.dat')
    data_10 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_10.dat')
    data_20 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_20.dat')

    plt.loglog(data_03[:, 0], data_03[:, 1], '-v')
    plt.loglog(data_05[:, 0], data_05[:, 1], '-^')
    plt.loglog(data_07[:, 0], data_07[:, 1], '-<')
    plt.loglog(data_10[:, 0], data_10[:, 1], '->')
    plt.loglog(data_20[:, 0], data_20[:, 1], '-s')

    plt.title('Average relaxation time for $C_u=0.5$')
    plt.legend(['p=0.03', 'p=0.05', 'p=0.07', 'p=0.10', 'p=0.20'], loc=4)
    plt.ylabel('relaxation time $\\tau$')
    plt.xlabel('domain size L')

    for point in data_03[:, 0]:
        plt.axvline(x=point, color='grey', linestyle=':', alpha=.4)

    plt.ylim(300, 7e4)
    plt.xlim(40, 140)
    plt.show()


def show_domain_relaxation_prob():
    data_03 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_03.dat')
    data_05 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_05.dat')
    data_07 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_07.dat')
    data_10 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_10.dat')
    data_20 = np.loadtxt(path + 'relaxation_time\\sm2d_domain_relaxation_20.dat')

    probs = np.array([0.03, 0.05, 0.07, 0.10, 0.20])
    time = np.array([data_03[:, 1][2], data_05[:, 1][2], data_07[:, 1][2], data_10[:, 1][2], data_20[:, 1][2]])
    alpha = np.log(time) / np.log(60)
    slopeX, interceptX, *restX = stats.linregress(probs, alpha)

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.plot(probs, alpha, '-o')
    plt.errorbar(probs, alpha, yerr=probs * slopeX + interceptX - alpha, fmt='ro', capsize=4)

    plt.title('Exponent $\\alpha$ of the average relaxation time. L = 60')
    plt.legend(['exponent $\\alpha$', '$\\alpha = p^{-0.5}$'])

    plt.ylabel('$\\alpha$')
    plt.xlabel('$p$')

    plt.ylim(1.7, 2.7)
    plt.xlim(.01, .25)
    plt.show()


# Domain: 50, sims: 1000
def show_decision_time_vs_prob_2d():
    data = np.loadtxt(path + 'decision_time_vs_prob\\sm2d_decision_time.dat')
    data03 = np.loadtxt(path + 'decision_time_vs_prob\\sm2d_decision_time_03.dat')
    data05 = np.loadtxt(path + 'decision_time_vs_prob\\sm2d_decision_time_05.dat')
    data07 = np.loadtxt(path + 'decision_time_vs_prob\\sm2d_decision_time_07.dat')
    data10 = np.loadtxt(path + 'decision_time_vs_prob\\sm2d_decision_time_10.dat')
    data20 = np.loadtxt(path + 'decision_time_vs_prob\\sm2d_decision_time_20.dat')

    fig, ax = plt.subplots()
    ax.yaxis.grid(color='gray', linestyle='dashed', alpha=.7)
    ax.xaxis.grid(color='gray', linestyle='dashed', alpha=.7)

    plt.loglog(data[:, 0], data[:, 1] / np.sum(data[:, 1]), '+')
    plt.loglog(data03[:, 0], data03[:, 1] / np.sum(data03[:, 1]), '--v')
    plt.loglog(data05[:, 0], data05[:, 1] / np.sum(data05[:, 1]), '--^')
    plt.loglog(data07[:, 0], data07[:, 1] / np.sum(data07[:, 1]), '--<')
    plt.loglog(data10[:, 0], data10[:, 1] / np.sum(data10[:, 1]), '-->')
    plt.loglog(data20[:, 0], data20[:, 1] / np.sum(data20[:, 1]), '--s')

    plt.title('Distribution of decision time $\mu$')
    plt.legend(['p=0.1', 'p=0.2', 'p=0.4', 'p=0.6', 'p=1'])
    plt.ylabel('$P(\mu)$')
    plt.xlabel('decision time $\mu$')

    plt.ylim(1e-6, .7)
    plt.xlim(3, 700)
    plt.show()


show_steady_state_1d()
show_steady_state_modified_1d()
show_decision_time_1d()

show_steady_state_2d()
show_relaxation_time_2d()
show_decision_time_2d()
show_decision_time_vs_domain_2d()
show_decision_change_2d()
show_decision_change_vs_domain_2d()

show_yes_fraction_2d()
show_yes_fraction_extended_2d()
show_domain_relaxation()
show_domain_relaxation_prob()
show_decision_time_vs_prob_2d()

