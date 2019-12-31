import os

from oeqa.runtime.case import OERuntimeTestCase
from oeqa.core.decorator.depends import OETestDepends
from oeqa.runtime.decorator.package import OEHasPackage

class JavacTest(OERuntimeTestCase):

    @classmethod
    def setUpClass(cls):
        myfilesdir = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../../files/')
        java_src = ['test.java', 'hello.java']
        for j in java_src:
            src = os.path.join(myfilesdir, j)
            dst = '/tmp/%s' % j
            cls.tc.target.copyTo(src, dst)

    @classmethod
    def tearDownClass(cls):
        java_src = ['test.java', 'hello.java']
        dst = []
        d = '/tmp'
        for j in java_src:
            jc = j.replace('.java', '.class')
            dst.append(os.path.join(d, j))
            dst.append(os.path.join(d, jc))
        dst = ' '.join(dst)
        cls.tc.target.run('rm %s' % dst)

    @OETestDepends(['java.JavaTest.test_java_exists'])
    def test_javac_exists(self):
        status, output = self.target.run('which javac')
        msg = 'javac binary not in PATH or not on target.'
        self.assertEqual(status, 0, msg=msg)

    @OETestDepends(['javac.JavacTest.test_javac_exists'])
    def test_javac_works(self):
        status, output = self.target.run('javac /tmp/test.java')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

    @OETestDepends(['javac.JavacTest.test_javac_works'])
    def test_java_runtime(self):
        status, output = self.target.run('javac /tmp/hello.java')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

        status, output = self.target.run('java -cp /tmp hello')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)
