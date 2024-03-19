class Cohort:

    def __init__(self, experiments=None, data_set=None, data_path=None, parameters=None,
                 method=None, step_size=1000, data=None, n=None):
        self.experiments = [] if experiments is None else experiments
        self.data_set = data_set
        self.data_path = data_path
        self.parameters = {} if parameters is None else parameters
        self.method = method
        self.step_size = step_size
        self.data = data
        self.n = n

    def load_cohort(self, root_dir):
        pass
