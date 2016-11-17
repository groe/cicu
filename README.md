# Cicu

[![Build Status](https://travis-ci.org/groe/cicu.png?branch=master)](http://travis-ci.org/groe/cicu)

Custom ICU rulesets for collation in ruby - requires libicu

## Installation

Add this line to your application's Gemfile:

    gem 'cicu'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install cicu

## Usage

Create a ruleset

    ```ruby
    ruleset = Cicu::Ruleset.new("[normalization on] & b < a < c")
    ```

Sort an array

    ```ruby
    ary = %w( a b c ba bb bc )
    sorted_ary = ruleset.sort_by { |el| ruleset.sort_key(el) }
    # => "["b", "bb", "ba", "bc", "a", "c"]"
    ```

Get the sort key for a string

    ```ruby
    ruleset.sort_key("abc")
    # => "*\x04)*\x05\x01\a\x01\a"
    ```

You can store sort keys in a database column to use them in `ORDER BY` queries. Make sure to use a column type that supports binary strings (e.g. MySQLs VARBINARY).

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
