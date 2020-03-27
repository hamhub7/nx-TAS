mkdocs build
ghp-import site
git push origin gh-pages
rm -Force -Recurse site
