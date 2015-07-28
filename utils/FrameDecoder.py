#!/usr/bin/python
from optparse import OptionParser

def Diff(idle_log, action_log):
    action_set = set(_process(open(action_log, 'r')))
    idle_set = set(_process(open(idle_log, 'r')))
    uniques = action_set - action_set.intersection(idle_set)
    return uniques

def _process(log_file):
    info = list()
    for line in log_file:
        if "Index" in line:
            continue
        fields = [item.strip() for item in line.split(',')]
        try:
            info.append(tuple([fields[3], fields[4], fields[5], fields[6]]))
        except Exception as e:
            print 'error %s on line #%s' % (e, str(fields[0]))
    return info

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-c', '--code-gen', action='store_true',
            default=False, dest='do_codegen', 
            help='generate C code for STM32 boards')
    parser.add_option('-i', '--idle-log', dest='idle_log',
            help='contains frames generated when car is idling')
    parser.add_option('-a', '--action-log', dest='action_log',
            help='contains frames generated when car does action we want to \
            reverse engineer')
    (options, args) = parser.parse_args()

    diff = Diff(options.idle_log, options.action_log)

    if options.do_codegen:
        print 'Copy and Paste the following into main.c in canbridge:'
        for item in diff:
            print 'TxMessage.ExtId = %s;\r' % item[1]
            print 'TxMessage.DLC = %s;\r' % item[2]
            data = item[3].split('  ')
            i = 0
            for hexNum in data:
                print 'TxMessage.Data[%s] = 0x%s;\r' % (i, hexNum)
                i += 1
            print 'CAN_Transmit(CANx, &TxMessage);\r'
            print '\r\n' # newlines in Windows format :(

    print 'Frames in action log file that are not in idle log file:'
    for item in diff:
        print item
