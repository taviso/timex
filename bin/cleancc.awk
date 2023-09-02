BEGIN {
    RS = "\r\n"
    print "include '../timex.inc'"
    print
}

END {
    print "UNDEF  SUBROUTINE"
    print "END"
}

# Remove assembler directives that we dont need.
$1 == "CALLS"   { next }
$1 == "$CASE"   { next }
$1 == "$MODEL"  { next }
$1 == "EXTERN"  { next }
$1 == "END"     { next }
/^\s*$/         { next }

# Optionally we can strip comments
#$1 == ";"       { next }

# Any handling for special units
$1 == "NAME"    {
    switch (substr($2, 2, length($2) - 2)) {
        case "COMMON":
            # This reference is needed so that the locator generates it, it's a
            # user-defined label so we can find the ApplicationStateManager address.
            print "EXTERN __lc_ub_asm"
            next;
        default:
            print "include 'common.equ'"
            print "defsect '.text', code"
            next
    }
}

# Remove useless instructions
$1 == "CARL" && $2 ~ /^__fallthrough_/ {
    next
}
$1 == "LD" && $2 == "ep,#00h" {
    next
}

# Section management
$1 == "DEFSECT" {

    # We need to remove any section option, we manage them here to make sure
    # they're compatible with the locator.
    NF = 3;

    # All sections are code. If we differentiate data and code, then the
    # locator will get confused about how to arrange short sections.
    # We basically just use sections for grouping and arrangement, nothing else.
    $3 = "code";

    switch (substr($2, 2, length($2) - 3)) {
        # These sections are allowed
        case ".text_COMMON":
        case ".rtcode":
        case ".ndata":
            break;
        # This is okay, but I generate a default one.
        case ".text":
        # Skip any others, because the locator wont recognize them.
        # You can add more if you want, just place them somewhere in the dsc file.
        default:
            next;
    }
}

$1 == "SECT"    {
    # Record the active section.
    section = substr($2, 2, length($2) - 2);

    switch (section) {
        # These sections are allowed
        case ".text_COMMON":
        case ".rtcode":
        case ".text":
        case ".ndata":
            break;
        # We fold any others into our .text section.
        default:
            $2 = "\".text\"";
            break;
    }

    print "Current section =>",section > "/dev/stderr"
}

# Generate SUBROUTINE directives, this makes any macros we call from inline
# assembly happy.
$1 == "GLOBAL"  {
    print "UNDEF  SUBROUTINE"
    print "DEFINE SUBROUTINE \"'",$2,"'\""
}

{ print }
