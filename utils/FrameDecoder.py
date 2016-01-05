#!/usr/bin/python
# TODO - clean up ignored id code organization
from optparse import OptionParser

def diff(idle_log, action_log): # returns ordered diff between action and idle
    action_info = _tuplify(open(action_log, 'r'))
    action_set = set(action_info)
    idle_set = set(_tuplify(open(idle_log, 'r')))
    uniques = action_set - action_set.intersection(idle_set)
    order = sorted([action_info.index(item) for item in uniques])
    return [action_info[idx] for idx in order]

def _tuplify(log_file): # turns log file into list of tuples of relavant fields
    info = list()
    if options.ignored_ids is '':
        ignored_ids = ()
    else:
        ignored_ids = tuple(options.ignored_ids.split(','))
    for line in log_file:
        if "Index" in line:
            continue
        fields = [item.strip() for item in line.split(',')]
        if fields[4].startswith(ignored_ids):
            continue

        try:
            info.append(tuple([fields[3], fields[4], fields[5], fields[6]]))
        except Exception:
	    print 'Warning - error reading line \n - %s' % line

    return info

def _code_gen(diff): # prints C code for writing the diff over CAN
    print 'TxMessage.IDE = CAN_Id_Extended;'
    print 'TxMessage.RTR = CAN_RTR_Data;'
    for item in diff:
        print 'TxMessage.ExtId = %s;' % item[1]
        print 'TxMessage.DLC = %s;' % item[2]
        data = item[3].split('  ')
        i = 0
        for hexNum in data:
            print 'TxMessage.Data[%s] = 0x%s;' % (i, hexNum)
            i += 1
        print 'CAN_Transmit(CANx, &TxMessage);'
	print 'Delay();Delay();Delay();'
        print '\r\n' # newlines in Windows format :(

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-c', '--code-gen', action='store_true',
            default=False, dest='do_codegen',
            help='generate C code for STM32 boards')
    parser.add_option('-i', '--idle-log', dest='idle_log',
            help='contains frames generated when car is idling')
    parser.add_option('-a', '--action-log', dest='action_log',
            help='contains frames generated when car does action we want to '\
            'reverse engineer')
    parser.add_option('-r', '--ignore', dest='ignored_ids', default='',
		    help='comma separated list of message IDs to' \
				    'ignore when generating diff')
    (options, args) = parser.parse_args()

    d = diff(options.idle_log, options.action_log)

    if options.do_codegen:
        _code_gen(d)

    else:
        print 'Frames in action log file that are not in idle log file:'
        for item in d:
            print item
