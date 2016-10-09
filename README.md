# R2ree

[r2ree](https://github.com/namusyaka/r2ree) bindings for Ruby

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'r2ree'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install r2ree

## Usage

```ruby
tree = R2ree.new(['/a', '/b', '/c'])

tree.size #=> 3
tree.find('/b') #=> 1
tree.exist?('/c') #=> true
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/namusyaka/r2ree-ruby.


## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).

