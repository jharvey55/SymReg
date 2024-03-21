import matplotlib.pyplot as plt
import primitives
from typing import List
import pandas as pd
import numpy as np

# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Learning Curves
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

opacity = 0.2
colors = [
    ('xkcd:burnt orange', opacity),
    ('xkcd:deep pink', opacity),
    ('xkcd:teal', opacity),
    ('xkcd:olive green', opacity),
    ('xkcd:mauve', opacity),
    ('xkcd:sea blue', opacity),
    ('xkcd:grape', opacity),
    ('xkcd:dark magenta', opacity),
    ('xkcd:denim blue', opacity),
    ('xkcd:tomato', opacity)
]

colors2 = [
    ('firebrick', opacity),
    ('indigo', opacity),
    ('darkolivegreen', opacity),
    ('darkblue', opacity),
    ('orange', opacity),
    ('darkslateblue', opacity),
    ('darkolivegreen', opacity),
    ('orchid', opacity),
    ('lightcoral', opacity),
    ('teal', opacity),
    ('olivedrab', opacity),
    ('deeppink', opacity),
    ('darkslateblue', opacity)
]
colors3 = [
    ('lightcoral', opacity),
    ('mediumpurple', opacity),
    ('yellowgreen', opacity),
    ('steelblue', opacity),
]


def plot_learning_curve(cohorts: List[primitives.Cohort]):
    """

    :param cohorts: list of cohorts
    :return:
    """

    fig, ax = plt.subplots()

    for i, cohort in enumerate(cohorts):
        # ax.scatter(x=cohort.data.evals, y=cohort.data.mean, label=cohort.method)
        # upper = cohort.data.mean + cohort.data.s_dev
        # lower= cohort.data.mean - cohort.data.s_dev
        # # error = [lower, upper]
        ax.errorbar(x=cohort.data.evals, y=cohort.data.mean, yerr=cohort.data.s_dev, label=cohort.method,
                    ecolor=colors3[i], color=colors2[i][0])

    ax.set_title("{} - Learning Curve".format(cohorts[0].data_set), fontsize=48)
    ax.legend()
    ax.set_xlabel("Evaluations", fontsize=24)
    ax.set_ylabel("Mean RMSE", fontsize=24)
    plt.show()
