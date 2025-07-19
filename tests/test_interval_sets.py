import reticula as ret


def test_interval_set_creation():
    intervals = ret.interval_set[ret.double]()
    intervals.insert(1.0, 2.0)
    intervals.insert(3.0, 4.0)

    assert 1.5 in intervals
    assert 3.5 in intervals
    assert 2.5 not in intervals
    assert 0.5 not in intervals


def test_interval_set_operations():
    intervals1 = ret.interval_set[ret.double]()
    intervals1.insert(1.0, 2.0)
    intervals1.insert(3.0, 4.0)

    intervals2 = ret.interval_set[ret.double]()
    intervals2.insert(1.5, 2.5)
    intervals2.insert(3.5, 4.5)

    assert 1.5 in intervals1
    assert 2.0 in intervals2

    intervals1.merge(intervals2)
    assert 2.2 in intervals1


def test_interval_set_with_integers():
    intervals = ret.interval_set[ret.int64]()
    intervals.insert(1, 3)
    intervals.insert(5, 7)

    assert 2 in intervals
    assert 6 in intervals
    assert 4 not in intervals


def test_empty_interval_set():
    intervals = ret.interval_set[ret.double]()

    assert 1.0 not in intervals
    assert 0.0 not in intervals
