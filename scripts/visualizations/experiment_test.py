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
        self.assertEqual(params['Evals'], "1s00000")
        self.assertEqual(params['Pop'], "250")
        self.assertEqual(params['GradPercent'], "0.250000")
        self.assertEqual(params['Tier'], "3")
        self.assertEqual(params['GradGen'], "10")


if __name__ == '__main__':
    unittest.main()
