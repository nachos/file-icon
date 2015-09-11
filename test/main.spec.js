'use strict';

var chai = require('chai');
var expect = chai.expect;

describe('file-icon', function () {
  var fileIcon = require('../lib');

  describe('exports', function () {
    it('should expose api', function () {
      expect(fileIcon.get).to.be.a('function');
    });
  });

  describe('asd', function () {
    it('asd', function () {
      var x = fileIcon.get();

      console.log(x);
    });
  });
});