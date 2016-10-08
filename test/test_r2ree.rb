require File.expand_path('helper', __dir__)

class TestR2ree < Test::Unit::TestCase
  sub_test_case 'r2ree basic interface' do
    test 'r2ree with no args' do
      assert_raise(ArgumentError) { R2ree.new }
    end

    test 'r2ree with empty array' do
      tree = R2ree.new([])
      assert_instance_of R2ree, tree
    end

    test 'r2ree with paths' do
      tree = R2ree.new(['/a', '/b'])
      assert_instance_of R2ree, tree
      assert_equal 2, tree.size
    end
  end

  sub_test_case '#size' do
    test 'assert correct size' do
      tree = R2ree.new(['/'])
      assert_equal 1, tree.size
    end

    test 'assert correct size even if very large size' do
      size = 100000
      tree = R2ree.new(size.times.to_a.map(&:to_s))
      assert_equal size, tree.size
    end

    test 'assert correct size even if path does not exist' do
      tree = R2ree.new([])
      assert_equal 0, tree.size
    end
  end

  sub_test_case '#exist?' do
    test 'assert to return true if path is appended' do
      tree = R2ree.new([?/])
      assert_equal true, tree.exist?(?/)
    end

    test 'assert to return false if path is not appended' do
      tree = R2ree.new(['/a'])
      assert_equal false, tree.exist?(?/)
    end
  end

  sub_test_case '#find' do
    test 'assert to return the added order of its path' do
      tree = R2ree.new([?/, '/a', '/b', '/c'])
      assert_equal 1, tree.find('/a')
      assert_equal 3, tree.find('/c')
    end

    test 'assert to return -1 if given path does not match with added paths' do
      tree = R2ree.new([?/, '/a'])
      assert_equal -1, tree.find('/foo')
      assert_equal -1, tree.find('//')
    end
  end
end
