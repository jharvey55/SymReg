import unittest
from data_vis.data_vis import Experiment


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



if __name__ == '__main__':
    unittest.main()
