'use strict';

var chai = require('chai');
var expect = chai.expect;

describe('file-icon', function () {
  var fileIcon = require('../lib');

  describe('exports', function () {
    it('should expose a function', function () {
      expect(fileIcon).to.be.a('function');
    });
  });
});