import shutil
import os
import random

TEMP = "temp"
IN_MEM_LIMIT = 100000

def commitToFile(fileIndex, tempDir, lines):
    newFile = open(os.path.join(tempDir, str(fileIndex)), "w")
    lines.sort(key=lambda x : int(x))
    for l in lines:
        newFile.write(l + "\n")

def commitRemaining(infile, outfile):
    for line in infile:
        line = line.strip()
        if line:
            outfile.write(line + '\n')

def filePathToTempDir(filePath):
    parentDir = os.path.dirname(os.path.abspath(filePath))
    tempDir = os.path.join(parentDir, TEMP)
    return tempDir

def breakFile(filePath):
    tempDir = filePathToTempDir(filePath)
    if not os.path.exists(tempDir):
        os.mkdir(tempDir)
    
    fileIndex = 0
    with open(filePath) as f:
        lines = []
        for line in f:
            if len(lines) == IN_MEM_LIMIT:
                commitToFile(fileIndex, tempDir, lines)
                lines.clear()
                fileIndex += 1
            lines.append(line.strip())

    if lines:
        commitToFile(fileIndex, tempDir, lines)
        fileIndex += 1

    return fileIndex

        
def mergeFiles(inputFileIds, tempDir):
    outputId = inputFileIds[-1] + 1
    outFileIds = []
    for i in range(0, len(inputFileIds)-1,2):
        infile1 = open(os.path.join(tempDir,str(inputFileIds[i])))
        infile2 = open(os.path.join(tempDir,str(inputFileIds[i+1])))
        outfile = open(os.path.join(tempDir, str(outputId)), "w")
        outFileIds.append(outputId)
        outputId += 1
        line1 = infile1.readline().strip()
        line2 = infile2.readline().strip()
        while line1 and line2:
            if int(line1) < int(line2):
                outfile.write(line1 + "\n")
                line1 = infile1.readline().strip()
            else:
                outfile.write(line2 + "\n")
                line2 = infile2.readline().strip()
        
        if line1:
            outfile.write(line1 + "\n")
            line1 = ""
        
        if line2:
            outfile.write(line2 + "\n")
            line2 = ""

        if infile1:
            commitRemaining(infile=infile1, outfile=outfile)

        if infile2:
            commitRemaining(infile=infile2, outfile=outfile)

        outfile.close()


    if len(inputFileIds) % 2 == 1:
        file1Path = os.path.join(tempDir,str(inputFileIds[-1]))
        outFilePath = os.path.join(tempDir, str(outputId))
        if os.path.exists(outFilePath):
            os.remove(outFilePath)
        os.rename(file1Path, outFilePath)
        outFileIds.append(outputId)

    return outFileIds

def externalSort(filepath):
    fileCount = breakFile(filepath)
    inputFileList = list(range(fileCount))
    tempDir = filePathToTempDir(filepath)
    while len(inputFileList)  != 1:
        inputFileList = mergeFiles(inputFileList, tempDir)

    # copy to outfile or input file (for in-place sorting)
    return os.path.join(tempDir, str(inputFileList[0]))

# Test code 
def generateAnInputFile(stringCnt, filepath):
    with open(filepath, "w") as f:
        while stringCnt:
            n = random.randint(1, stringCnt)
            f.write(str(n) + "\n")
            stringCnt -= 1


if __name__ == "__main__":
    inputFile = "input.txt"
    generateAnInputFile(1000000, inputFile)
    outputFile = externalSort(inputFile)
    print(outputFile)
