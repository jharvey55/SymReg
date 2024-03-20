import os
import data_vis
import numpy as np


class Contender:
    def __init__(self, evals=None, fitness=None, solution=None):
        """

        :param evals: int representing the evaluation for contenders.
        :param fitness: float representing fitness of solution
        :param solution: representation of solution
        """
        self.evals = evals
        self.fitness = fitness
        self.solution = solution

    @classmethod
    def read_in_contender(cls, line):
        """
        Creates a contender from a line in a file with components split by " | "
        :param line: Log String
        :return: Contender built form line components
        """

        [evals_string, fitness_string, solution_string] = line.split(' | ')
        evals = int(evals_string)
        fitness = float(fitness_string)
        solution = solution_string.rstrip("\n").rstrip(" ").lstrip(" ")

        contender = cls(evals, fitness, solution)
        return contender


class Experiment:
    def __init__(self, exp_path=None, data_set=None, run_time=None, params=None, method=None, contenders=None):
        """

        :param exp_path:  Path to experiment directory
        :param data_set: Name of Dataset
        :param run_time: Timestamp for experiment run
        :param params: Experiment parameters
        :param method: Optimization Method
        :param contenders: List of contenders
        """
        self.exp_path = exp_path
        self.data_set = data_set
        self.run_time = run_time
        self.params = params
        self.method = method
        self.contenders = [] if contenders is None else contenders

    @classmethod
    def parse_params(cls, line):
        """
        Turns line into dictionary containing parameters of the experiment
        :param line: string of parameters in format <key>:value> seperated by a space
        :return: dictionary containing parameters for the experiment
        """
        params = {}
        pairs = line.split(" ")
        for pair in pairs:
            parts = pair.split(":")
            params[parts[0]] = parts[1]

        return params

    @classmethod
    def read_in_experiment(cls, path):
        """
        reads in experiment at the provided path
        :param path: location of experiment log file to be read in
        :return: experiment object containing data from  log file
        """

        exp = Experiment()
        exp.path = path

        with open(path, 'r') as f:
            index = 0
            line = f.readline()

            while line != '':
                line = line.rstrip('\n')
                if index == 0:
                    exp.data_set = line.split('\t')[1]
                elif index == 1:
                    exp.run_time = line.split('\t')[1]
                elif index == 2:

                    exp.method = line.split('\t')[1]
                elif index == 3:
                    exp.params = cls.parse_params(line.split('\t')[1])
                elif index > 7:
                    exp.contenders.append(Contender.read_in_contender(line))
                line = f.readline()
                index += 1
        return exp

    def get_eval_index(self, target, start=0):
        """

        :param target: evaluations of contender to beat
        :param start: guess to minimize loop length if possible
        :return: index of contender with the greatest number of evals that do not exceed target
        """
        cap = len(self.contenders)
        if start > cap:
            raise IndexError(f"Start out of contenders range")

        index = start
        while index + 1 < cap and self.contenders[index + 1].evals <= target:
            index += 1
        return index


class DataPoint:

    def __init__(self, average=0, stdev=0, evals=0):
        """
        Object for storing aggregated data point in learning curve
        :param average: Average fitness for best Contender at evals
        :param stdev: Standard deviation for best Contender at evals
        :param evals: Number of evals for all points in theis datapoint
        """
        self.average = average
        self.stdev = stdev
        self.evals = evals


class Cohort:

    def __init__(self, experiments=None, data_set=None, parameters=None,
                 method=None, step_size=None, data=None, n=None):
        """

        :param experiments: list of experiments in Cohort
        :param data_set: Name of dataset used in experiment
        :param parameters: dictionary of parameters used across experiments
        :param method: method used by all experiments in cohort
        :param step_size: frequency of data aggregation points
        :param data: aggregated points for the experiments
        :param n: number of experiments in cohort
        """
        self.experiments = [] if experiments is None else experiments
        self.data_set = data_set
        self.parameters = {} if parameters is None else parameters
        self.method = method
        self.step_size = step_size
        self.data = data
        self.n = n

    def tabulate(self):
        """
        Creates the learning dataset at given intervals
        """
        indices = []
        budget = int(self.parameters['E'])
        points = []
        point = np.array([])

        # Set up structures and fill first data point
        for exp in self.experiments:
            indices.append(0)
            point = np.append(point, exp.contenders[0].fitness ** 2)
        points.append(DataPoint(np.mean(point), np.std(point), 1))

        # Finish populating data points
        for target in range(1, budget, self.step_size):
            point = np.array([])
            for i, exp in enumerate(self.experiments):
                indices[i] = self.experiments[i].get_eval_index(target, indices[i])
                point = np.append(point, exp.contenders[indices[i]].fitness ** 2)
            points.append(DataPoint(np.mean(point), np.std(point), target))
        self.data = points

    @classmethod
    def build_cohort(cls, root_dir, step_size=1000):
        """
        Builds cohort object out of experiments in root_dir
        :param root_dir: directory of experiments to be aggregated
        :param step_size: sampling frequency in evaluations
        :return: Cohort object with aggregated data
        """
        cohort = Cohort()
        exp_list = os.listdir()
        cohort.n = len(exp_list)
        for e in exp_list:
            # Get experiment learn file and add experiment to cohort
            file = "{}_learn.txt".format(e)
            wd = os.path.join(root_dir, e, file)
            cohort.experiments.append(Experiment.read_in_experiment(wd))
        cohort.data_set = cohort.experiments[0].data_set
        cohort.method = cohort.experiments[0].method
        cohort.step_size = step_size

        cohort.tabulate()
        return cohort
