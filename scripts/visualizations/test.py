import unittest
from data_vis.data_vis import Contender
from data_vis.data_vis import Experiment


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
