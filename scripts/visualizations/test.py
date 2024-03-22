import sys
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

    def test_parse_values(self):
        x = 3.0
        pos_big_str = str(sys.float_info.max)
        neg_big_str = str(-1 * sys.float_info.max)

        # y = x
        eq_var = ["ROOT", "VAR"]
        r_x = Contender.parse_values(1, x, eq_var)
        self.assertEqual(x, r_x, "Did not parse basic VAR correctly")

        # Addition tests
        eq_add = ["ROOT", "ADD", "VAR", "2.0"]
        r_add = Contender.parse_values(1, x, eq_add)
        self.assertEqual(5.0, r_add, "Did not parse basic ADD correctly")

        eq_add_2 = ["ROOT", "ADD", pos_big_str, pos_big_str]
        r_add_2 = Contender.parse_values(1, x, eq_add_2)
        self.assertEqual(Contender.big, r_add_2, "Did not parse pos inf ADD correctly")

        eq_add_3 = ["ROOT", "ADD", neg_big_str, neg_big_str]
        r_add_3 = Contender.parse_values(1, x, eq_add_3)
        self.assertEqual(-1.0 * Contender.big, r_add_3, "Did not parse neg inf ADD correctly")

        # Subtraction tests
        eq_sub = ["ROOT", "SUB", "VAR", "2.0"]
        r_sub = Contender.parse_values(1, x, eq_sub)
        self.assertEqual(1.0, r_sub, "Did not parse basic SUB correctly")

        eq_sub_2 = ["ROOT", "SUB", neg_big_str, pos_big_str]
        r_sub_2 = Contender.parse_values(1, x, eq_sub_2)
        self.assertEqual(-1.0 * Contender.big, r_sub_2, "Did not parse neg inf SUB correctly")

        eq_sub_3 = ["ROOT", "SUB", pos_big_str, neg_big_str]
        r_sub_3 = Contender.parse_values(1, x, eq_sub_3)
        self.assertEqual(Contender.big, r_sub_3, "Did not parse pos inf SUB correctly")

        # Multiplication tests
        eq_mlt = ["ROOT", "MLT", "VAR", "2.0"]
        r_mlt = Contender.parse_values(1, x, eq_mlt)
        self.assertEqual(6.0, r_mlt, "Did not parse basic MLT correctly")

        eq_mlt_2 = ["ROOT", "MLT", pos_big_str, pos_big_str]
        r_mlt_2 = Contender.parse_values(1, x, eq_mlt_2)
        self.assertEqual(Contender.big, r_mlt_2, "Did not parse pos inf MLT correctly")

        eq_mlt_3 = ["ROOT", "MLT", pos_big_str, neg_big_str]
        r_mlt_3 = Contender.parse_values(1, x, eq_mlt_3)
        self.assertEqual(-1.0 * Contender.big, r_mlt_3, "Did not parse neg inf MLT correctly")
        # Division tests
        eq_div = ["ROOT", "DIV", "VAR", "2.0"]
        r_div = Contender.parse_values(1, x, eq_div)
        self.assertEqual(1.5, r_div, "Did not parse basic DIV correctly")

        eq_div_2 = ["ROOT", "DIV", -1.0, 0.0]
        r_div_2 = Contender.parse_values(1, x, eq_div_2)
        self.assertEqual(-1.0 * Contender.big, r_div_2, "Did not parse neg inf DIV correctly")

        eq_div_3 = ["ROOT", "DIV", 1.0, 0.0]
        r_div_3 = Contender.parse_values(1, x, eq_div_3)
        self.assertEqual(Contender.big, r_div_3, "Did not parse pos inf DIV correctly")

        # Sine tests
        eq_sin = ["ROOT", "SIN", "VAR", "BLANK"]
        r_sin = Contender.parse_values(1, x, eq_sin)
        self.assertEqual(0.1411200080598672, r_sin)

        # Cosine tests
        eq_cos = ["ROOT", "COS", "VAR", "BLANK"]
        r_cos = Contender.parse_values(1, x, eq_cos)
        self.assertEqual(-0.9899924966004454, r_cos)


if __name__ == '__main__':
    unittest.main()
