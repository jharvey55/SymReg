import unittest
from data_vis.data_vis import Experiment
from data_vis.data_vis import Contender


class TestExperiment(unittest.TestCase):
    def test_parse_params(self):
        """
        Tests if parse_params returns the correct params
        :return:
        """
        sample = "Params:	DotLog:110 DivLog:110 Evals:100000 Pop:250 GradPercent:0.250000 Tier:3 GradGen:10"
        params = Experiment.parse_params(sample.split('\t')[1])
        self.assertEqual(params['DotLog'], "110")
        self.assertEqual(params['DivLog'], "110")
        self.assertEqual(params['Evals'], "100000")
        self.assertEqual(params['Pop'], "250")
        self.assertEqual(params['GradPercent'], "0.250000")
        self.assertEqual(params['Tier'], "3")
        self.assertEqual(params['GradGen'], "10")

    def test_read_in_experiment(self):
        path = "../../examples/f1/results/f1_HFC-Cross_2024`3`8-0`13`43/f1_HFC-Cross_2024`3`8-0`13`43_learn.txt"
        result = Experiment.read_in_experiment(path)

        # data set
        self.assertEqual(result.data_set, "f1")

        # Params
        self.assertEqual(result.params['DotLog'], "110")
        self.assertEqual(result.params['DivLog'], "110")
        self.assertEqual(result.params['Evals'], "100000")
        self.assertEqual(result.params['Pop'], "250")
        self.assertEqual(result.params['GradPercent'], "0.250000")
        self.assertEqual(result.params['Tier'], "3")
        self.assertEqual(result.params['GradGen'], "10")

        # Contenders
        self.assertEqual(result.contenders[0].evals, 250)
        self.assertEqual(result.contenders[0].fitness, 0.507485)
        self.assertEqual(result.contenders[0].eq[0], "ROOT")
        self.assertEqual(result.contenders[0].eq[1], "SIN")
        self.assertEqual(result.contenders[0].eq[25], "BLANK")
        self.assertEqual(result.contenders[0].eq[-1], "BLANK")

    def test_parse_values(self):
        x = 3.0
        eq1 = ["ROOT", "VAR"]

        eq2 = ["ROOT", "ADD", "VAR", "2.0"]
        eq3 = ["ROOT", "SUB", "VAR", "2.0"]
        eq4 = ["ROOT", "MLT", "VAR", "2.0"]
        eq5 = ["ROOT", "DIV", "VAR", "2.0"]
        eq6 = ["ROOT", "ADD", "VAR", "2.0"]


class TestContender(unittest.TestCase):
    def test_read_in_contender(self):
        """
        Test if read_in_contender(line) creates a stable
        :return:
        """
        a = ("250 | 0.507485 | ROOT SIN SIN BLANK SUB BLANK BLANK BLANK COS DIV BLANK BLANK BLANK BLANK BLANK BLANK "
             "SUB BLANK ADD MLT BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK 8.583254 VAR "
             "BLANK BLANK -5.630509 VAR VAR VAR BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK "
             "BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK "
             "BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK "
             "BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK "
             "BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK "
             "BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK\n")
        contender = Contender.read_in_contender(a)
        self.assertEqual(contender.evals, 250)
        self.assertEqual(contender.fitness, 0.507485)
        self.assertEqual(contender.eq[0], "ROOT")
        self.assertEqual(contender.eq[1], "SIN")
        self.assertEqual(contender.eq[25], "BLANK")
        self.assertEqual(contender.eq[-1], "BLANK")


if __name__ == '__main__':
    unittest.main()
