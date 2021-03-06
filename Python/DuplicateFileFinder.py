import hashlib
import glob
import os

class DuplicateFinder(object):

	def __init__(self, dirToSearch):
		if not dirToSearch:
			print "Empty directory, failed to find duplicates" 
			return
		self.__curDir = dirToSearch
		self.__fileListOfCurDir = []
		self.__dupFileDict={}
		self.__digests = []
		self.__chunk = 2**7
		self.__fileSize = 0
		#self.hasher = hashlib.md5()
	def __del__(self):
		self.__curDir = ""
		self.__fileListOfCurDir = []
		self.__dupFileDict={}
		self.__digests = []
		self.__chunk = 0
		self.__fileSize = 0
		
	def __readFileInChunks(self, f, fName, chunSize = 2**7):
		localHasher=hashlib.md5()
		while True:
			buf = f.read(chunSize)
			if not buf:
				break
			localHasher.update(buf)
		
		hexDigest = localHasher.hexdigest()
		return hexDigest
	def __calculate_hash(self, fName):
		
		localHasher = hashlib.md5()
		self.__fileSize = os.path.getsize(fName)
		with open(fName, 'r') as f:
			if self.__fileSize > self.__chunk:
				a = self.__readFileInChunks(f, fName)
			else:
				buf = f.read()
				localHasher.update(buf)
			
			a = localHasher.hexdigest()

			#print "File Size:[" , self.fileSize ,"]B","Name:[", fName ,"]Hash:[", a,"]"
			if self.__dupFileDict.has_key(a) == False:
				self.__dupFileDict[a] = fName
			else:
				print "[" ,fName , "] already found![" ,fName , "]and[" , self.__dupFileDict[a] ,"]are same!"

			#self.hexDigest = self.hasher.hexdigest()
	def __listFiles(self):
		self.__fileListOfCurDir = glob.glob(self.__curDir)
		#print "List of files:", self.__fileListOfCurDir

	#Only public function open for users to call to find duplicate file in the current directory
	def findDuplicates(self):
		self.__listFiles()
		self.__iterateAllFiles()
	def __iterateAllFiles(self):
		#print "File Count:" , len(self.__fileListOfCurDir)
		for filename in self.__fileListOfCurDir:
			#to avoid computing hash of the source file
			if __file__.split()[-1].split("/")[-1] == filename:
				continue
			if not os.path.isfile(filename):
				continue
			#print "Calculating Hash: of file:[", filename ,"]"
			self.__calculate_hash(filename)

########var = DuplicateFinder("*")##var.findDuplicates()